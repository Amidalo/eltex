#include "customer.h"

/**
 * 
 */
void* customer_thread(void* arg)
{
    struct customer* customer = (struct customer*) arg;
    int customer_id = customer->id;
    int need = (rand() % (MAX_NEED - MIN_NEED + 1)) + MIN_NEED;
    
    printf("\n Появился покупатель %d, текущая потребность %d. \n",
        customer_id, need);

    while (need > 0)
    {
        int bought = 0;

        for (int i = 0; i < ACTIVE_STORES; i++)
        { // захватываем мьютекс ларька
            pthread_mutex_lock(&customer->market_ptr->stores[i].mutex);

            int available_products = customer->market_ptr->stores[i].products;

            if (available_products > 0)
            {
                printf("\n Покупатель %d пришел в ларек %d, доступных продуктов %d. \n",
                    customer_id, i, available_products);

                bought = (need < available_products) ? need : available_products;

                customer->market_ptr->stores[i].products -= bought;
                need -= bought;

                printf("\n Покупатель %d купил %d продуктов, осталось потребности %d. \n",
                    customer_id, bought, need);

                if (need <= 0)
                {
                    pthread_mutex_unlock(&customer->market_ptr->stores[i].mutex);
                    break;
                }
            }

            pthread_mutex_unlock(&customer->market_ptr->stores[i].mutex);
        }

        if (need > 0)
        {
            printf("\n Покупатель %d не смог до конца насытится, уходит в сон 2 сек \n", customer_id);
            sleep(2);
            printf("\n Покупатель %d проснулся \n", customer_id);
        }
    }

    printf("\n Покупатель %d полностью насытился. \n", customer_id);

    pthread_mutex_lock(&customer->market_ptr->main_mutex);
    customer->market_ptr->number_of_active_customers--;

    if (customer->market_ptr->number_of_active_customers == 0)
    {
        customer->market_ptr->loader_work_flag = 0;
        printf("\n Покупатель %d был последним. Нужно остановить работу погрузчика. \n",
            customer_id);
    }

    pthread_mutex_unlock(&customer->market_ptr->main_mutex);
    
    return NULL;
}