#include "server.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "agent.h"
#include "screen.h"

#ifdef __cplusplus
extern "C" {
#endif

int listenfd = 0;

int getlistenfd() {
	return listenfd;
}

void server() {
	int confd;
    pthread_t tid;
    struct sockaddr_in servaddr, cliaddr;
    int len;
    char addrp[160];
    char clientname[HOSTNAME_MAXLENGTH];
    int clientname_len;
    char buf[1000];

	if (pthread_create(&screen_read_tid, NULL, screen_read_thread, NULL) != 0) printf("thread!\n");

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(APP_PORT);
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (listen(listenfd, CONNECT_MAXNUM) == -1) 
		puts("listen failed");

	puts("listening");

	while (1) {
		confd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
		if (confd == -1) {
			puts("quit the application");
			break;
		}

		inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, addrp, len);
		clientname_len = read(confd, clientname, HOSTNAME_MAXLENGTH);
		clientname[clientname_len] = '\0';
		write(confd, gethostname(), gethostnamelen());

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%s joined the network\n", clientname);
		printf("%s", buf);

		sendout(buf, strlen(buf), -1);
		store_con(confd, clientname, clientname_len, addrp, strlen(addrp));

		if (pthread_create(&tid, NULL, con_agent_server_thread, &confd) != 0)
			puts("thread creation failed\n");
	}
}

#ifdef __cplusplus
}
#endif
