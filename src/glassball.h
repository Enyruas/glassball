#ifndef GLASSBALL_GLASSBALL_H_
#define GLASSBALL_GLASSBALL_H_

#include <stdio.h>
#include <netinet/in.h>
#ifdef __cplusplus
extern "C" {
#endif

#define CON_MAXNUM 100

extern int confds[CON_MAXNUM];
extern int con_num;

struct con_info {
	int confd;
	struct sockaddr conaddr;
};

// definition of common data types and methods

#ifdef __cplusplus
}
#endif

#endif
