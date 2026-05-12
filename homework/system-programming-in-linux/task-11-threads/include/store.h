#ifndef _STORE_H_
#define _STORE_H_

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MIN_PRODUCTS 900
#define MAX_PRODUCTS 1100

/**
 * Это ларек, хранит в себе количество продуктов и мютекс
 */
struct store
{
    int products;
    pthread_mutex_t mutex;
};

/**
 * 
 */
void init_store(struct store* store);

/**
 * 
 */
void destroy_store(struct store* store);

#endif