#ifndef GLASSBALL_AGENT_H_
#define GLASSBALL_AGENT_H_

#include <pthread.h>

#include "glassball.h"

#ifdef __cplusplus
extern "C" {
#endif

void con_agent_tid_push(pthread_t tid);

void *con_agent_thread(void *arg);

#ifdef __cplusplus
}
#endif

#endif //GLASSBALL_AGENT_H_
