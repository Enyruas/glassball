#ifndef GLASSBALL_CLIENT_H_
#define GLASSBALL_CLIENT_H_

#include <sys/select.h>

#include <iostream>
#include <string>

#include "glassball.h"

class Client {
  public:
    Client(std::string hostname, std::string address="127.0.0.1");
    ~Client();

    void start();
	std::string hostName() const { return hostName_; }
	std::string serverName() const { return serverName_; }
	void setServerName(std::string serverName) { serverName_ = serverName; }
  private:
    int doSocket(int domain, int type, int protocol);
    int doConnect(std::string address);
	std::string hostName_;
	std::string serverName_;
	std::string address_;
    int confd_;
    fd_set set_;
};

#endif // GLASSBALL_CLIENT_H_
