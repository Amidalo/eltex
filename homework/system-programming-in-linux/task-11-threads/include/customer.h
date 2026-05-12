#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include <pthread.h>
#include <market.h>
#include <unistd.h>

#define ACTIVE_CUSTOMERS 3
#define MIN_NEED 9900
#define MAX_NEED 10100

/**
 * 
 */
struct customer
{
    struct market* market_ptr;
    int id;
};

void* customer_thread(void* arg);

#endif