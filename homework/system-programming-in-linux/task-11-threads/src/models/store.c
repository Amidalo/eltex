#include "store.h"

/**
 * 
 */
void init_store(struct store* store)
{
    if (store == NULL)
    {
        printf("Ошибка: объект store - NULL!");
        return;
    }

    store->products = (rand() % (MAX_PRODUCTS - MIN_PRODUCTS + 1)) + MIN_PRODUCTS;

    if (pthread_mutex_init(&store->mutex, NULL) != 0)
    {
        printf("Ошибка: мьютекс не был проинициализирован!");
        return;
    }
    
    return;
}

/**
 * 
 */
void destroy_store(struct store* store)
{
    if (store != NULL)
    {
        pthread_mutex_destroy(&store->mutex);
    }
    
    return;
}