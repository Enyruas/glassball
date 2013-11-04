#ifndef GLASSBALL_SERVER_H_
#define GLASSBALL_SERVER_H_

#include "BasicIO.h"

#include <poll.h>

#include <iostream>
#include <list>
#include <string>
#include <vector>

class Server: public BasicIO {
  public:
    Server(std::string hostName = std::string());
    ~Server();

	void start();
	void broadcastOut(const char *buf, int len, int excldconfd);
	void broadcastOut(const std::string str, int excldconfd);

  private:
    int doBind();
    int doListen();
    int doAccept(struct sockaddr_in &cliaddr, int &len);
	void exchangeName(int confd, struct sockaddr_in &cliaddr, int len);

    std::list<con_T> confds_;

    int listenfd_;

	std::vector<struct pollfd> pollfds_;
	void addPollfd(int fd) {
		int i = 0;
		for (; i < pollfds_.size(); i++)
			if (pollfds_[i].fd == -1) {
				pollfds_[i].fd = fd;
				pollfds_[i].events = POLLRDNORM;
				break;
			}
		if (i == pollfds_.size())
			pollfds_.push_back((struct pollfd){.fd=fd, .events=POLLRDNORM});
	}
	int doPoll(int timeout) {
		poll(&(pollfds_[0]), pollfds_.size(), timeout);
	}
};


#endif // GLASSBALL_SERVER_H_
