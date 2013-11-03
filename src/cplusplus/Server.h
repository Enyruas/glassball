#ifndef GLASSBALL_SERVER_H_
#define GLASSBALL_SERVER_H_

//#include "glassball.h"

#include <sys/select.h>

#include <iostream>
#include <vector>
#include <string>

class Server {
  public:
    Server(std::string hostName = std::string());
    ~Server();

    void start();
	std::string hostName() const { return hostName_; }
	void setHostName(std::string hostName) { hostName_ = hostName; }
	void broadcastOut(const char *buf, int len, int excldconfd);
	void broadcastOut(const std::string str, int excldconfd);

    static const int kConnectMaxnum = 100;

  private:
    int doSocket(int domain, int type, int protocol);
    int doBind();
    int doListen();
    int doAccept(struct sockaddr_in &cliaddr, int &len);
	void exchangeName(int confd, struct sockaddr_in &cliaddr, int len);

	std::string hostName_;

    typedef struct con_T{
        int fd;
        std::string clientName;
	std::string ipaddress;
	con_T(int _fd, std::string _clientName, std::string _ipaddress): 
		fd(_fd), clientName(_clientName), ipaddress(_ipaddress) {}
    }con_T;
    std::vector<con_T> confds_;

    int listenfd_;
    fd_set set_;
};


#endif // GLASSBALL_SERVER_H_
