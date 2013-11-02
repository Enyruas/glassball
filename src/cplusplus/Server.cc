#include "Server.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#include "glassball.h"
/*#include "agent.h"
#include "screen.h"*/
#include "Stream.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

Server::Server(std::string hostName): hostName_(hostName), confds_(), listenfd_(0) {
//	FD_ZERO(set_);
}
	
Server::~Server() { }

int Server::socket(int domain, int type, int protocol) {
	int fd = socket(domain, type, protocol);
	if (fd < 0) 
		ERRSTREAM<<"socket error";
	return fd;
}

int Server::bind() {
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(APP_PORT);

	assert(listenfd_);
	int retVal = ::bind(listenfd_, reinterpret_cast<struct sockaddr *>(&servaddr), sizeof(servaddr));
	if (retVal != 0)
		ERRSTREAM<<"bind error";
	return retVal;
}

int Server::listen() {
	assert(listenfd_);
	int retVal = ::listen(listenfd_, CONNECT_MAXNUM);
	if (retVal == -1)
		ERRSTREAM<<"listen failed";
	return retVal;
}

int Server::accept(struct sockaddr_in &cliaddr, int &len) {
	assert(listenfd_);
	int confd = ::accept(listenfd_, (struct sockaddr *)&cliaddr, (socklen_t *)&len);
	if (confd < 0)
		ERRSTREAM<<"accept error";
	return confd;
}

void Server::broadcastOut(const std::string &buf, int excldconfd) {
    for (std::vector<con_T>::iterator it = confds_.begin();
			it != confds_.end();
			it++) {
		if (it->fd != excldconfd)
			;//::write();//(it->fd, buf.c_str(), buf.length());
    }
}

void Server::start() {
    struct sockaddr_in servaddr, cliaddr;
    int len;

	listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
	bind();
	listen(); 
	SCREENSTREAM<<"listening";
	
	FD_ZERO(&set_);
	FD_SET(listenfd_, &set_);
	FD_SET(fileno(stdin), &set_);
	int maxfdp1 = max(fileno(stdin), listenfd_) + 1;

	while (1) {
		int setNum = select(confds_.size(), &set_, NULL, NULL, NULL);

		// handle select error
		if (setNum < 0) {
			ERRSTREAM<<"select wrong";
			continue;
		}
		// handle the connection from clients
		if (FD_ISSET(listenfd_, &set_)) {
			int confd = accept(cliaddr, len);
			if (confd == -1) {
				SCREENSTREAM<<"quit the application";
				continue;
			}
			
			else {
			    char addrp[160];
			    char clientname[HOSTNAME_MAXLENGTH];
			    int clientname_len;
			    char buf[1000];

				inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, addrp, len);
//				clientname_len = read(confd, clientname, HOSTNAME_MAXLENGTH);
				clientname[clientname_len] = '\0';
			//	write(confd, hostName_.c_str(), hostName_.length());

				std::string str(clientname);
				confds_.push_back(con_T(confd, str, std::string(addrp)));

				str += " joined the network\n";
				SCREENSTREAM<<str;
				broadcastOut(str, -1);
			}
			if (--setNum <= 0)
				continue;
		}
		// read from clients
		for (std::vector<con_T>::iterator it = confds_.begin();
				it != confds_.end();
				it++) {
			if (FD_ISSET(it->fd, &set_)) {
				char buf[100];
			//	int len = read(it->fd, buf, 100);
				std::string str(buf);
				SCREENSTREAM<<str;
				broadcastOut(str, -1);

				if (--setNum <= 0)
					break;	
			}
		}
	}
}

