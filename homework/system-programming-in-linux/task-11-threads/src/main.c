/**
 * @file    main.c
 * @author  amidalo
 * @date    10-Март-2026
 * 
 * @brief Реализация логики точки входа.
 */

#include "customer.h"
#include "store.h"
#include "market.h"
#include "loader.h"
#include <time.h>

/**
 * @brief Точка входа в программу.
 * 
 * @details Алгоритм работы функции:
 * 1. Инициализируем маркет, ларьки.
 * 2. Создаем массив покупателей и массив их потоков, создаем сами потоки.
 * 3. Создаем поток погрузчика.
 * 4. Ждем завершения потоков покупателей и потока погрузчика.
 * 5. Уничтожаем мьютексы ларьков и главный мьютекс.
 */
int main(void)
{
    srand(time(NULL));

    // 1
    struct market market;
    init_market(&market);

    for (int i = 0; i < ACTIVE_STORES; i++)
    {
        init_store(&market.stores[i]);
        printf("Ларек %d на старте имеет %d товаров. \n", i, market.stores[i].products);
    }

    // 2
    struct customer customers[ACTIVE_CUSTOMERS];
    pthread_t threads[ACTIVE_CUSTOMERS];

    for (int i = 0; i < ACTIVE_CUSTOMERS; i++)
    {
        customers[i].id = i + 1;
        customers[i].market_ptr = &market;
        pthread_create(&threads[i], NULL, customer_thread, (void*)&customers[i]);
    }

    // 3
    pthread_t loader;
    pthread_create(&loader, NULL, loader_thread, (void*) &market);

    // 4
    for (int i1 = 0; i1 < ACTIVE_CUSTOMERS; i1++)
    {
        pthread_join(threads[i1], NULL);
    }

    pthread_join(loader, NULL);

    // 5
    for (int i = 0; i < ACTIVE_STORES; i++)
    {
        pthread_mutex_destroy(&market.stores[i].mutex);
    }

    pthread_mutex_destroy(&market.main_mutex);
    
    return 0;
}