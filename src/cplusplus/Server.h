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

	int listenfd_;
	std::list<con_T> confds_;
	std::vector<struct pollfd> pollfds_;

	std::string getConfdClientName(int fd);
	void delConfd(int fd);

	int doPoll(int timeout);
	void initializePollfd();
	void addPollfd(int fd);

	bool pollListenCall() const;
	bool pollStdinCall() const;

	int getPollConCallIndex() const;
	int getPollfd(int index) const;
	void delPollfd(int index);
};


#endif // GLASSBALL_SERVER_H_
