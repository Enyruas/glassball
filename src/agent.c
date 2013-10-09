#include "agent.h"

#include <netinet/in.h>

#include "glassball.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BUF_MAXLEN 100

static pthread_t *con_agent_tid;

void con_agent_tid_push(pthread_t tid) {

}

void *con_agent_thread(void *arg) {
	char buf[BUF_MAXLEN+1];
	int buf_len;
	int confd = *((int *)arg);
	char address[14];
	//strcpy(address, con_info_pt->conaddr.sa_data);
	while (1) {
		if (read(confd, buf, BUF_MAXLEN) == -1) {
			printf("connect terminated\n");
			break;
		}
		fputs(buf, stdout);
	}
	
}


void start_agent() {
//  recv_process = fork();
//  write_process = fork();
}

#ifdef __cplusplus
}
#endif
