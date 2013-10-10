#ifndef GLASSBALL_GLASSBALL_H_
#define GLASSBALL_GLASSBALL_H_

#include <stdio.h>
#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HOSTNAME_MAXLENGTH 255
#define CONNECT_MAXNUM 100
#define APP_PORT 50432

extern int mode;

extern char hostname[];
extern int hostname_len;

//extern int confds[CON_MAXNUM];
extern int con_num;

typedef struct {
	int confd;
	char hostname[HOSTNAME_MAXLENGTH];
	char ipaddress[16];
}con_info_t;

extern con_info_t con_infos[CONNECT_MAXNUM];

void store_con(int confd, char hostname[], int hostname_len, char ipaddress[], int ipaddress_len);

int delede_con(int confd);

int get_con(int confd, char hostname[], char ipaddress[]);

// definition of common data types and methods

#ifdef __cplusplus
}
#endif

#endif
