#ifndef GLASSBALL_SERVER_H_
#define GLASSBALL_SERVER_H_

#include "BasicIO.h"

#include <sys/select.h>

#include <iostream>
#include <vector>
#include <string>

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

    std::vector<con_T> confds_;

    int listenfd_;
    fd_set set_;
};


#endif // GLASSBALL_SERVER_H_
