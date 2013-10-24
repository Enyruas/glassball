#ifndef GLASSBALL_SERVER_H_
#define GLASSBALL_SERVER_H_

#include "glassball.h"

#ifdef __cplusplus
extern "C" {
#endif

int getlistenfd();

void server();

#ifdef __cplusplus
}
#endif

#endif // GLASSBALL_SERVER_H_
