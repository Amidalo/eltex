#ifndef _LOADER_H_
#define _LOADER_H_

#include <pthread.h>
#include <market.h>
#include <unistd.h>

void* loader_thread(void* arg);

#endif