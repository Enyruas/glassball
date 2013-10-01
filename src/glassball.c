#include "glassball.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
  int fd;
  pid_t childpid; 
  char input[100];
  int mode, server, client;
//  socket(AF_INET, SOCK_STREAM, 0)
  // select net mode

  if (mode == server) {
    //call server method in servor.h
  }
  else if (mode == client) {
    //call client method in client.h

  }

  
  if ((childpid = fork()) == 0) {
     sleep(2);
     printf("this is the child process\n");
       return 0;
     }
  printf("plese input: ");
  scanf("%s", input);
  printf("the input is: %s\n", input);

  return 0;
}
