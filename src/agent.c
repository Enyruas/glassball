#include "agent.h"

#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "glassball.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BUF_MAXLEN 100

void sendout(const char *buf, int buf_len, int excldconfd) {
    int i;

    for (i = 0; i < con_num; i++) {
		if (con_infos[i].confd != excldconfd)
	        write(con_infos[i].confd, buf, buf_len);
    }   
}

int recvfromcon(int confd, char buf[]) {
	int buf_len;
	if ((buf_len = read(confd, buf, BUF_MAXLEN)) < 0) {
		puts("connect terminated\n");
		return -1;
	}

	buf[buf_len] = '\0';
	return buf_len;	
}

void *con_agent_server_thread(void *arg) {
	int confd = *(int *)arg;
	char buf[BUF_MAXLEN+1];
	char name[HOSTNAME_MAXLENGTH], address[16];
	int buf_len;

	while (1) {
		if ((buf_len = recvfromcon(confd, buf)) <= 0) {
			if (get_screen_read_open() == 1) {
				shutdown(confd, SHUT_WR);

				if (get_con(confd, name, address) == -1)
		            puts("getcon failed");
	    	    sprintf(buf, "%s exited\n", name);
        		printf("%s", buf);
		        sendout(buf, strlen(buf), confd);
	    	    delete_con(confd);
			}
			close(confd);
			break;
		}
		write(fileno(stdout), buf, buf_len);
		sendout(buf, buf_len, confd);
	}
}

void con_agent_client_thread(int confd) {
	char buf[BUF_MAXLEN+1];
	int buf_len;
	char address[16], name[HOSTNAME_MAXLENGTH];
	while (1) {
		if ((buf_len = recvfromcon(confd, buf)) <= 0) {
			if (get_screen_read_open() == 1) {
				shutdown(confd, SHUT_WR);

				if (get_con(confd, name, address) == -1)
					puts("getcon failed");
				sprintf(buf, "%s exited\n", name);
				printf("%s", buf);
			} else puts("quit glassball!");

			close(confd);
			delete_con(confd);
			break;
		}
		write(fileno(stdout), buf, buf_len);
	}
}

#ifdef __cplusplus
}
#endif
