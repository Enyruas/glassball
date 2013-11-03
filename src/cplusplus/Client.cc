#include "Client.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Stream.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

Client::Client(std::string hostname, std::string address): hostName_(hostname), address_(address) {

}

Client::~Client() {
}

int Client::doSocket(int domain, int type, int protocol) {
        int fd = socket(domain, type, protocol);
        if (fd < 0)  
                ERRSTREAM<<"socket error";
        return fd; 
}

int Client::doConnect(std::string address) {
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(APP_PORT);
    int retVal = 0;
    if ((retVal = inet_pton(AF_INET, address.c_str(), &servaddr.sin_addr)) < 0) {
	ERRSTREAM<<"inet_pton error for";
	return retVal;
    }

    if ((retVal = ::connect(confd_, (struct sockaddr *)&servaddr, sizeof(servaddr))) == -1) {
	ERRSTREAM<<"connect failed";
	return retVal;
    }
}
 
void Client::start() {
    char servername[HOSTNAME_MAXLENGTH];
   int servername_len;

	confd_ = doSocket(AF_INET, SOCK_STREAM, 0);
	doConnect(address_);
	
	write(confd_, hostName().c_str(), hostName().length());
        servername_len = read(confd_, servername, HOSTNAME_MAXLENGTH);
        servername[servername_len] = '\0';
	setServerName(std::string(servername));
        SCREENSTREAM<<"you joined "<<servername<<"'s network\n";

	int stdineof = 0;
	int maxfd = 0;
	
	for ( ; ; ) {
		FD_ZERO(&set_);
		FD_SET(confd_, &set_);
		maxfd = max(maxfd, confd_);
	   	if (stdineof == 0) {
			FD_SET(fileno(stdin), &set_);
			maxfd = max(fileno(stdin), confd_);
		}
		int setNum = select(maxfd+1, &set_, NULL, NULL, NULL);
		if (setNum < 0) {
			ERRSTREAM<<"select wrong";
			continue;
		}

		if (FD_ISSET(confd_, &set_)) {
		    	char buf[100];
			int nread = read(confd_, buf, 99); 
			if (nread == 0) {
				if (stdineof == 1)
					SCREENSTREAM<<"You exited glassball\n";
				else 
					SCREENSTREAM<<serverName()<<" exited glassball\n";
				return;
			} else {
				buf[nread] = '\0';
			    	SCREENSTREAM<<buf;;
			}

	    		if (--setNum <= 0)
				continue;
		}

	if (FD_ISSET(fileno(stdin), &set_)) {
	    	char buf[100];
	   	fgets(buf, 100, stdin);
		if (buf[0] == '\n') {
			shutdown(confd_, SHUT_WR); /* send FIN */
			FD_CLR(fileno(stdin), &set_);
			stdineof = 1;
		} else {
			std::string str = hostName() + ": " + buf;
			write(confd_, str.c_str(), str.length());
		}
		if (--setNum <= 0)
			continue;
	}
    }
}
