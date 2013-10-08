#include "glassball.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "screen.h"
#include "agent.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APP_PORT 50432

int mode;

int confds[CON_MAXNUM];
int con_num;

int main(int argc, char *argv[]) {
	int listenfd, confd;
	pid_t childpid; 
	pthread_t tid;
	char input[100];
	int server, client;
	char *s;
	struct sockaddr_in servaddr, cliaddr;
	int len;
	char address[16];
	const int LISTENQ = 5;


	// select net mode
	while (s = fgets(input, 100, stdin)) {
    	sscanf(s, "%d", &mode);
		printf("mode=%d\n", mode);
		switch (mode) {
		case 0:
	    //call server method in servor.h
    		mode = create_server();
			
			// start write show
			if (pthread_create(&screen_read_tid, NULL, screen_read_thread, NULL) != 0) printf("thread!\n");
			
			//  socket(AF_INET, SOCK_STREAM, 0)
			listenfd = socket(AF_INET, SOCK_STREAM, 0);
		
			bzero(&servaddr, sizeof(servaddr));
			servaddr.sin_family = AF_INET;
			servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
			servaddr.sin_port = htons(APP_PORT);
			bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
			if (listen(listenfd, LISTENQ) == -1) printf("listen failed\n");
			printf("afeter listen\n");			

			while (1) {
				len = sizeof(cliaddr);
				confd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
				if (confd == -1)
					continue;
				printf("there is a connection\n");

				confds[con_num++] = confd;

				if (pthread_create(&tid, NULL, con_agent_thread, &confd) != 0)
				printf("thread creation failed\n");
				con_agent_tid_push(tid);
			//record this new thread
			// push(tid);
				sleep(1);
			}
    		break;
    
		case 1: 
    //call client method in client.h
//      mode = create_client();
			fgets(address, 16, stdin);

			confd = socket(AF_INET, SOCK_STREAM, 0);
			bzero(&servaddr, sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            servaddr.sin_port = htons(APP_PORT);
			if (inet_pton(AF_INET, address, &servaddr.sin_addr) < 0)
				printf("inet_pton error for %s", address);
			printf("address=%s\n", address);
	
			if (connect(confd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) printf("connect failed\n");
			printf("after connect\n");
			if (pthread_create(&screen_read_tid, NULL, screen_read_thread, NULL) != 0) printf("thread!\n");

			confds[con_num++] = confd;
			con_agent_thread(&confd);

			break;

		defaut:
			;
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

#ifdef __cplusplus
}
#endif
