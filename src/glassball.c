#include "glassball.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "screen.h"
#include "agent.h"

int main(int argc, char *argv[]) {
  int fd, confd;
  pid_t childpid; 
	pthread_t tid;
  char input[100];
  int mode, server, client;
	char *s;
//  socket(AF_INET, SOCK_STREAM, 0)
  // select net mode

  while (s = fgets(input, 100, stdin)) {
    
    if (mode == server) {
    //call server method in servor.h
    	mode = create_server();
		// start write show
		if (pthread_create(&screen_print_tid, NULL, screen_print_thread, NULL) != 0) printf("thread!\n");
		if (pthread_create(&screen_scan_tid, NULL, screen_scan_thread, NULL) != 0) printf("thread!\n");
		while (1) {
//			confd = accept();
			if (pthread_create(&tid, NULL, com_agent_thread, &confd) != 0)
				printf("thread creation failed\n");
			com_agent_tid_push(tid);
			//record this new thread
			// push(tid);
			sleep(1);
		}
    }
    
    else if (mode == client) {
    //call client method in client.h
//      mode = create_client();
    }
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
