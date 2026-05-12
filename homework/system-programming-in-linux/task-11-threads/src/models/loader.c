#include "loader.h"

/**
 * 
 */
void* loader_thread(void* arg)
{
    struct market* market = (struct market*) arg;
    
    printf("\n Погрузчик начинает свою работу. \n");

    while (1)
    {
        pthread_mutex_lock(&market->main_mutex);
        int status = market->loader_work_flag;
        pthread_mutex_unlock(&market->main_mutex);

        if (status == 0) // inactive
        {
            break;
        }
        
        int random_store_id = rand() % ACTIVE_STORES;
        pthread_mutex_lock(&market->stores[random_store_id].mutex);

        market->stores[random_store_id].products += 200;
        printf("\n Погрузчик завез 200 продуктов в ларек %d, итого %d продуктов. \n",
            random_store_id, market->stores[random_store_id].products);

        pthread_mutex_unlock(&market->stores[random_store_id].mutex);

        printf("\n Погрузчик уехал за новым товаром. \n");
        sleep(1);
    }
    
    printf("\n Погрузчик завершает свою работу. \n");

    return NULL;
}