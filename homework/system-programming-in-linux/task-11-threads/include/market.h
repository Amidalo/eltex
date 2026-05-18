/**
 * @file    market.h
 * @author  amidalo
 * @date    10-Март-2026
 * 
 * @brief Интерфейс управления магазином.
 */

#ifndef _MARKET_H_
#define _MARKET_H_

#include <stdio.h>
#include <pthread.h>
#include <store.h>

/**
 * @brief Макрос ACTIVE_STORES N, где N - кол-во активных ларьков в магазине.
 */
#define ACTIVE_STORES 5

/**
 * @brief Описание структуры магазина.
 * 
 * @details Содержит информацию о магазине: массив ларьков, кол-во активных
 * покупателей, флаг активности погрузчика, главный мьютекс для защиты данных
 * магазина.
 */
struct market
{
    struct store stores[ACTIVE_STORES];
    int number_of_active_customers;
    int loader_work_flag;
    pthread_mutex_t main_mutex;
};

/**
 * @brief Объявление функции, которая инициализирует магазин.
 * 
 * @details При инициализации магазин активизирует погрузчик, получает
 * количество активных покупателей, затем инициализирует главный мьютекс
 * для защиты своих данных от гонок.
 */
void init_market(struct market* market);

#endif