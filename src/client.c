#include "client.h"

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

void client() {
	int confd;
    struct sockaddr_in servaddr, cliaddr;
    char address[16];
    char servername[HOSTNAME_MAXLENGTH];
    int servername_len;

	if (pthread_create(&screen_read_tid, NULL, screen_read_thread, NULL) != 0) printf("thread!\n");

	printf("input the server address: ");
	fgets(address, 16, stdin);

	confd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(APP_PORT);
	if (inet_pton(AF_INET, address, &servaddr.sin_addr) < 0)
		printf("inet_pton error for %s", address);

	if (connect(confd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
		 printf("connect failed\n");

	write(confd, gethostname(), gethostnamelen());
	servername_len = read(confd, servername, HOSTNAME_MAXLENGTH);
	servername[servername_len] = '\0';
	printf("you joined %s's network\n", servername);

	store_con(confd, servername, servername_len, address, sizeof(address));
	con_agent_client_thread(confd);
}

#ifdef __cplusplus
}
#endif
