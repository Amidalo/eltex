/**
 * @file    store.h
 * @author  amidalo
 * @date    10-Март-2026
 * 
 * @brief   Интерфейс управления ларьком.
 */

#ifndef _STORE_H_
#define _STORE_H_

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/**
 * @brief Макрос MIN_PRODUCTS N, где N - минимальное количество продуктов,
 * которое есть в ларьке.
 */
#define MIN_PRODUCTS 900

/**
 * @brief Макрос MAX_PRODUCTS N, где N - максимальное количество продуктов,
 * которое есть в ларьке.
 */
#define MAX_PRODUCTS 1100

/**
 * @brief Описание структуры ларька.
 * 
 * @details Содержит информацию о ларьке: количество продуктов,
 * мьютекс - гарант того, что в ларьке будет лишь один
 * поток покупателя.
 */
struct store
{
    int products;
    pthread_mutex_t mutex;
};

/**
 * @brief Объявление функции, которая инициализирует ларек.
 * 
 * @details При инициализации ларек получает рандомное количество
 * продуктов в диапазоне от MIN_PRODUCTS до MAX_PRODUCTS, а затем
 * инициализирует мьютекс.
 */
void init_store(struct store* store);

#endif