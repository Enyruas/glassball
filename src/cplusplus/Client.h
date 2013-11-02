#ifndef GLASSBALL_CLIENT_H_
#define GLASSBALL_CLIENT_H_

#include <sys/select.h>

#include <iostream>
#include <string>

#include "glassball.h"

class Client {
  public:
    Client(std::string hostname);
    ~Client();

    void start();

  private:
    int socket(int domain, int type, int protocol);
    int connect(char address[]);
    std::string hostname_;
    int confd_;
    fd_set set_;
};

#endif // GLASSBALL_CLIENT_H_
