#ifndef GLASSBALL_BASICIO_H_
#define GLASSBALL_BASICIO_H_

#include <sys/socket.h>

#include <iostream>
#include <string>

#include "Stream.h"

class BasicIO {
  public:
	BasicIO(std::string hostName = std::string()): hostName_(hostName) {}
	~BasicIO() {}

        std::string hostName() const { return hostName_; }
        void setHostName(std::string hostName) { hostName_ = hostName; }

	virtual void start() = 0;
  protected:
	std::string hostName_;
	int doSocket(int domain, int type, int protocol) {
		int fd = socket(domain, type, protocol);
	        if (fd < 0)  
         	       ERRSTREAM<<"socket error";
	        return fd; 
	}

    	typedef struct con_T{
        	int fd; 
	        std::string clientName;
	        std::string ipaddress;
        	con_T(int _fd, std::string _clientName, std::string _ipaddress): 
                	fd(_fd), clientName(_clientName), ipaddress(_ipaddress) {}
	}con_T;
};

#endif
