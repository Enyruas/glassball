#ifndef GLASSBALL_AGENT_H_
#define GLASSBALL_AGENT_H_

#include <pthread.h>

#include "glassball.h"

#ifdef __cplusplus
extern "C" {
#endif

void con_agent_tid_push(pthread_t tid);

void sendout(const char *buf, int buf_len, int excldconfd);

void *con_agent_server_thread(void *arg);

void con_agent_client_thread(int confd);

#ifdef __cplusplus
}
#endif

#endif //GLASSBALL_AGENT_H_
