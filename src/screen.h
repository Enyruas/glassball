#ifndef GLASSBALL_SCREEN_H_
#define GLASSBALL_SCREEN_H_

#include <pthread.h>

#include "glassball.h"

#ifdef __cplusplus
extern "C" {
#endif

extern pthread_t screen_read_tid;

void open_screen_read();

void close_screen_read();

int get_screen_read_open();

void *screen_read_thread(void *arg);

#ifdef __cplusplus
}
#endif

#endif //GLASSBALL_SCREEN_H_
