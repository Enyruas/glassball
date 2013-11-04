#ifndef GLASSBALL_CLIENT_H_
#define GLASSBALL_CLIENT_H_

#include "BasicIO.h"

#include <sys/select.h>

#include <iostream>
#include <string>

class Client: public BasicIO {
  public:
    Client(std::string hostname, std::string address="127.0.0.1");
    ~Client();

	void start();
	std::string serverName() const { return serverName_; }
	void setServerName(std::string serverName) { serverName_ = serverName; }
  private:
    	int doConnect(std::string address);
	std::string serverName_;
	std::string address_;
    	int confd_;
    	fd_set set_;
};

#endif // GLASSBALL_CLIENT_H_
