/**
 * 
 */

#include "market.h"
#include "customer.h"

/**
 * 
 */
void init_market(struct market* market)
{
    if (market == NULL)
    {
        printf("Ошибка: объект market - NULL");
        return;
    }

    market->loader_work_flag = 1; // active
    market->number_of_active_customers = ACTIVE_CUSTOMERS;
    
    if (pthread_mutex_init(&market->main_mutex, NULL) != 0)
    {
        printf("Ошибка: главный мьютекс не был проинициализирован!");
        return;
    }

    return;
}