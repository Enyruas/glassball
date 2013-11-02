#include "Client.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Stream.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

Client::Client(std::string hostname): hostname_(hostname) {

}

Client::~Client() {
}

int Client::socket(int domain, int type, int protocol) {
        int fd = socket(domain, type, protocol);
        if (fd < 0)  
                ERRSTREAM<<"socket error";
        return fd; 
}

int Client::connect(char address[]) {
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(APP_PORT);
    int retVal = 0;
    if ((retVal = inet_pton(AF_INET, address, &servaddr.sin_addr)) < 0) {
	ERRSTREAM<<"inet_pton error for";
	return retVal;
    }

    if ((retVal = ::connect(confd_, (struct sockaddr *)&servaddr, sizeof(servaddr))) == -1) {
	ERRSTREAM<<"connect failed";
	return retVal;
    }
}
 
void Client::start() {
//	int confd;
  //  struct sockaddr_in servaddr, cliaddr;
  //  char servername[HOSTNAME_MAXLENGTH];
   // int servername_len;

    char address[16];
    printf("input the server address: ");
    fgets(address, 16, stdin);

    connect(address);

    FD_ZERO(&set_);
    FD_SET(confd_, &set_);
    FD_SET(fileno(stdin), &set_);
    int maxfdp1 = max(fileno(stdin), confd_) + 1;

    for ( ; ; ) {
	int setNum = select(maxfdp1, &set_, NULL, NULL, NULL);

	if (setNum < 0) {
	    ERRSTREAM<<"select wrong";
	    continue;
	}

	if (FD_ISSET(confd_, &set_)) {
	    char buf[100];
	    //read
	    
	    SCREENSTREAM<<buf;
	    if (--setNum <= 0)
		continue;
	}

	if (FD_ISSET(fileno(stdin), &set_)) {
	    char buf[100];
	    //read
	    SCREENSTREAM<<buf;
	    if (--setNum <= 0)
		continue;
	}
/*
	write(confd, gethostname(), gethostnamelen());
	servername_len = read(confd, servername, HOSTNAME_MAXLENGTH);
	servername[servername_len] = '\0';
	printf("you joined %s's network\n", servername);

	store_con(confd, servername, servername_len, address, sizeof(address));
	con_agent_client_thread(confd);*/
    }
}
