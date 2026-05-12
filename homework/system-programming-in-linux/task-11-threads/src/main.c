/**
 * 
 */

#include "customer.h"
#include "store.h"
#include "market.h"
#include "loader.h"
#include <time.h>

/**
 * 
 */
int main(void)
{
    srand(time(NULL));

    struct market market;
    init_market(&market);

    for (int i = 0; i < ACTIVE_STORES; i++)
    {
        init_store(&market.stores[i]);
        printf("Ларек %d на старте имеет %d товаров. \n", i, market.stores[i].products);
    }

    struct customer customers[ACTIVE_CUSTOMERS];
    pthread_t threads[ACTIVE_CUSTOMERS];

    for (int i = 0; i < ACTIVE_CUSTOMERS; i++)
    {
        customers[i].id = i + 1;
        customers[i].market_ptr = &market;
        pthread_create(&threads[i], NULL, customer_thread, (void*)&customers[i]);
    }

    pthread_t loader;
    pthread_create(&loader, NULL, loader_thread, (void*) &market);

    for (int i1 = 0; i1 < ACTIVE_CUSTOMERS; i1++)
    {
        pthread_join(threads[i1], NULL);
    }

    pthread_join(loader, NULL);

    for (int i = 0; i < ACTIVE_STORES; i++)
    {
        destroy_store(&market.stores[i]);
    }
    
    return 0;
}