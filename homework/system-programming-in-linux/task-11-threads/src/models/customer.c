/**
 * @file    customer.c
 * @author  amidalo
 * @date    10-Март-2026
 * 
 * @brief Реализация логики покупателя.
 */

#include "customer.h"

/**
 * @brief Функция потока, выполняющего логику покупателя.
 * 
 * @details Алгоритм покупателя:
 * 1.Проверяет переданный параметр (ссылка на уже 
 * проинициализированного покупателя) на NULL.
 *  1.1 Если NULL, то возвращает управление. 
 * 2. Инициализирует указатель на структуру customer переданным параметром.
 * Генерирует рандомно потребность покупателя.
 * 3. Пока потребность > 0:
 *  3.1 Проходимся по каждому ларьку в маркете
 *  3.2 Блокирем мьютекс ларька, если это возможно
 *  3.3 Проверяем количество доступных продуктов.
 *  3.4 Если есть, то берем столько, сколько нужно.
 *  3.5 Если после этого потребности больше нет, сразу освобождаем мьютекс 
 *  ларька, выходим из цикла for (3.1), так как больше нет смысла ходить 
 *  по ларькам, и попадем в пункт 3.7, проверку не пройдем, так как 
 *  покупатель насытился.
 *      3.5.1 После проверки в while попадаем в этот пункт. Занимаем 
 *      главный мьютекс, чтобы уменьшить кол-во активных покупателей. Если
 *      покупатель был последним, то он останавливает работу погрузчика.
 *  3.6 Если потребность еще есть, то идем в следующий ларек, перед этим
 *  освободив мьютекс текущего ларька.
 *  3.7 Если после прохода по всем ларькам у покупателя все еще осталась
 *  потребность, то уводим его в сон на 2 секунды.
 */
void* customer_thread(void* arg)
{
    // 1
    if (arg == NULL)
    {
        // 1.1
        printf("Ошибка (customer): объект arg - NULL!");
        return NULL;
    }
    // 2
    struct customer* customer = (struct customer*) arg;
    int customer_id = customer->id;
    int need = (rand() % (MAX_NEED - MIN_NEED + 1)) + MIN_NEED;
    
    printf("\n Появился покупатель %d, текущая потребность %d. \n",
        customer_id, need);

    while (need > 0)
    {
        int bought = 0;

        // 3.1
        for (int i = 0; i < ACTIVE_STORES; i++)
        {
            // 3.2
            pthread_mutex_lock(&customer->market_ptr->stores[i].mutex);

            // 3.3
            int available_products = customer->market_ptr->stores[i].products;

            // 3.4
            if (available_products > 0)
            {
                printf("\n Покупатель %d пришел в ларек %d, доступных продуктов %d. \n",
                    customer_id, i, available_products);

                bought = (need < available_products) ? need : available_products;

                customer->market_ptr->stores[i].products -= bought;
                need -= bought;

                printf("\n Покупатель %d купил %d продуктов, осталось потребности %d. \n",
                    customer_id, bought, need);

                    // 3.5
                if (need <= 0)
                {
                    pthread_mutex_unlock(&customer->market_ptr->stores[i].mutex);
                    break;
                }
            }

            // 3.6
            pthread_mutex_unlock(&customer->market_ptr->stores[i].mutex);
        }

        // 3.7
        if (need > 0)
        {
            printf("\n Покупатель %d не смог до конца насытится, уходит в сон 2 сек \n",
                customer_id);
            sleep(2);
            printf("\n Покупатель %d проснулся \n", customer_id);
        }
    }

    // 3.5.1
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