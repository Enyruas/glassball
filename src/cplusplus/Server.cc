#include "Server.h"

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <string.h>

#include "glassball.h"
#include "Stream.h"

Server::Server(std::string hostName): BasicIO(hostName), confds_(), listenfd_(0) {

}
	
Server::~Server() { 

}

int Server::doBind() {
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(APP_PORT);

	assert(listenfd_);
	int retVal = bind(listenfd_, reinterpret_cast<struct sockaddr *>(&servaddr), sizeof(servaddr));
	if (retVal != 0)
		ERRSTREAM<<"bind error";
	return retVal;
}

int Server::doListen() {
	assert(listenfd_);
	int retVal = listen(listenfd_, CONNECT_MAXNUM);
	if (retVal == -1)
		ERRSTREAM<<"listen failed";
	return retVal;
}

int Server::doAccept(struct sockaddr_in &cliaddr, int &len) {
	assert(listenfd_);
	int confd = accept(listenfd_, (struct sockaddr *)&cliaddr, (socklen_t *)&len);
	if (confd < 0)
		ERRSTREAM<<"accept error";
	return confd;
}

void Server::broadcastOut(const char *buf, int len, int excldconfd) {
    for (std::vector<con_T>::iterator it = confds_.begin();
			it != confds_.end();
			it++) {
		if (it->fd != -1 && it->fd != excldconfd)
			write(it->fd, buf, len);
    }
}

void Server::broadcastOut(const std::string str, int excldconfd) {
	broadcastOut(str.c_str(), str.length(), excldconfd);
}

void Server::exchangeName(int confd, struct sockaddr_in &cliaddr, int len) {
	char clientname[HOSTNAME_MAXLENGTH];
	int clientname_len = read(confd, clientname, HOSTNAME_MAXLENGTH+1);
	clientname[clientname_len] = '\0';
	std::string str(clientname);

	write(confd, hostName().c_str(), hostName().length());

	char addrp[160];
	inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, addrp, len);
	confds_.push_back(con_T(confd, str, std::string(addrp)));

	str += " joined the network\n";
	SCREENSTREAM<<str;
	broadcastOut(str, confd);
}

void Server::start() {

	if ((listenfd_ = doSocket(AF_INET, SOCK_STREAM, 0)) < 0)
		return;
	if (doBind() < 0)
		return;
	if (doListen() < 0)
		return;
	SCREENSTREAM<<"Listening...\n";

	while (1) {
		FD_ZERO(&set_);
		FD_SET(listenfd_, &set_);
		FD_SET(fileno(stdin), &set_);
		int maxfd = max(fileno(stdin), listenfd_);
		
		for (std::vector<con_T>::iterator it = confds_.begin();
				it != confds_.end();
				it++) {
			if (it->fd != -1) {
				FD_SET(it->fd, &set_);			
				maxfd = max(maxfd, it->fd);
			}
		}

		int setNum = select(maxfd+1, &set_, NULL, NULL, NULL);

		// handle select error
		if (setNum < 0) {
			ERRSTREAM<<"select wrong";
			continue;
		}

		if (FD_ISSET(fileno(stdin), &set_)) {
			char buf[100];	
			fgets(buf, 100, stdin);
			if (buf[0] == '\n') {
				for (std::vector<con_T>::iterator it = confds_.begin();
					it != confds_.end();
					it++) 
					if (it->fd != -1) 
						close(it->fd);			
				SCREENSTREAM<<"You exited glassball\n";
				return;
			} else {
				std::string str = hostName() + ": " + buf;
				broadcastOut(str, -1);
			}
			if (--setNum <= 0)
				continue;
		}
		// handle the connection from clients
		if (FD_ISSET(listenfd_, &set_)) {
			struct sockaddr_in cliaddr;
			int len;
			int confd = doAccept(cliaddr, len);
			if (confd == -1) 
				SCREENSTREAM<<"quit the application";
			else exchangeName(confd, cliaddr, len);

			if (--setNum <= 0)
				continue;
		}
		// read from clients
		for (std::vector<con_T>::iterator it = confds_.begin();
				it != confds_.end();
				it++) {
			if (FD_ISSET(it->fd, &set_)) {
				char buf[100];
				int nread = read(it->fd, buf, 99);
				if (nread == 0) {
					close(it->fd);
					FD_CLR(it->fd, &set_);
					it->fd = -1;
					std::string str = it->clientName + " exited glassball\n";
					SCREENSTREAM<<str;
					broadcastOut(str, -1);
				} else {
					buf[nread] = '\0';
					SCREENSTREAM<<buf;
					broadcastOut(buf, strlen(buf), it->fd);
				}

				if (--setNum <= 0)
					break;	
			}
		}
	}
}

