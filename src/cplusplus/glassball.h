#ifndef GLASSBALL_GLASSBALL_H_
#define GLASSBALL_GLASSBALL_H_

#include <stdio.h>
#include <netinet/in.h>

#define HOSTNAME_MAXLENGTH 255
#define CONNECT_MAXNUM 100
#define APP_PORT 50432

int getmode();

const char *gethostname();
int gethostnamelen();

typedef struct {
	int confd;
	char hostname[HOSTNAME_MAXLENGTH];
	char ipaddress[16];
}con_info_t;

extern con_info_t con_infos[CONNECT_MAXNUM];
extern int con_num;

void store_con(int confd, char hostname[], int hostname_len, char ipaddress[], int ipaddress_len);
int delede_con(int confd);
void close_cons();
void shutdown_cons();
int get_con(int confd, char hostname[], char ipaddress[]);

#endif
