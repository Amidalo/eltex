/**
 * @file    market.c
 * @author  amidalo
 * @date    10-Март-2026
 * 
 * @brief   Реализация логики магазина, в котором находятся ларьки.
 */

#include "market.h"
#include "customer.h"

/**
 * @brief Реализация функции, которая инициализирует магазин.
 * 
 * @details Алгоритм работы функции:
 * 1. Проверяет переданный параметр на NULL.
 *  1.1 Если NULL -> возвращает управление.
 * 2. Инициализирует флаг погрузчика -> active (1) и кол-во активных покупателей.
 * 3. Инициализирует главный мьютекс и проверяет, что функция инициализации мьютекса
 * вернула 0 <- успешная инициализация.
 *  3.1 Если !=0 -> возвращает управление.
 * 
 * @param [in,out] market Указатель на структуру магазина.
 * На входе: адрес магазина.
 * На выходе: инициализированный магазин.
 */
void init_market(struct market* market)
{
    // 1
    if (market == NULL)
    {
        // 1.1
        printf("Ошибка: объект market - NULL");
        return;
    }

    // 2
    market->loader_work_flag = 1; // active
    market->number_of_active_customers = ACTIVE_CUSTOMERS;
    
    // 3
    if (pthread_mutex_init(&market->main_mutex, NULL) != 0)
    {
        // 3.1
        printf("Ошибка: главный мьютекс не был проинициализирован!");
        return;
    }

    return;
}