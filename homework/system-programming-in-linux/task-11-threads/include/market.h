#ifndef _MARKET_H_
#define _MARKET_H_

#include <stdio.h>
#include <pthread.h>
#include <store.h>

#define ACTIVE_STORES 5

/**
 * 
 */
struct market
{
    struct store stores[ACTIVE_STORES];
    int number_of_active_customers;
    int loader_work_flag;
    pthread_mutex_t main_mutex;
};

/**
 * 
 */
void init_market(struct market* market);



#endif