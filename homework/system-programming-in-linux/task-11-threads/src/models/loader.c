/**
 * @file    loader.c
 * @author  amidalo
 * @date    10-Март-2026
 * 
 * @brief Реализация логики погрузчика.
 */

#include "loader.h"

/**
 * @brief Функция потока, выполняющего логику погрузчика.
 * 
 * @details Алгоритм погрузчика:
 * 1.Проверяет переданный параметр (ссылка на магазин) на NULL.
 *  1.1 Если NULL, то возвращает управление. 
 * 2. Инициализирует указатель на структуру market переданным параметром.
 * 3. В критической области читает флаг активности погрузчика, блокируя 
 * мьютекс маркета (магазина).
 * 4. Если status = 0 -> inactive, то break.
 *  4.1 Погрузчик завершает работу.
 * 5. Выбирается рандомный ларек в маркете, блокируется его мьютекс,
 * завозится 200 продуктов, погрузчик уходит в сон на 1 секунду, 
 * мьютекс ларька освобождается.
 * 
 */
void* loader_thread(void* arg)
{
    // 1
    if (arg == NULL)
    {
        // 1.1
        printf("Ошибка (loader): объект arg - NULL!");
        return NULL;
    }

    // 2
    struct market* market = (struct market*) arg;
    
    printf("\n Погрузчик начинает свою работу. \n");

    while (1)
    {
        // 3
        pthread_mutex_lock(&market->main_mutex);
        int status = market->loader_work_flag;
        pthread_mutex_unlock(&market->main_mutex);

        // 4
        if (status == 0)
        {
            break;
        }
        
        // 5
        int random_store_id = rand() % ACTIVE_STORES;

        pthread_mutex_lock(&market->stores[random_store_id].mutex);
        market->stores[random_store_id].products += 200;
        printf("\n Погрузчик завез 200 продуктов в ларек %d, итого %d продуктов. \n",
            random_store_id, market->stores[random_store_id].products);
        pthread_mutex_unlock(&market->stores[random_store_id].mutex);

        printf("\n Погрузчик уехал за новым товаром. \n");
        sleep(1);
    }
    // 4.1
    printf("\n Погрузчик завершает свою работу. \n");

    return NULL;
}