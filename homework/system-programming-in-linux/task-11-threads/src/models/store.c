/**
 * @file    store.c
 * @author  amidalo
 * @date    10-Март-2026
 * 
 * @brief   Реализация логики ларька.
 */

#include "store.h"

/**
 * @brief   Реализация функции, которая инициализирует ларек.
 * 
 * @details Алгоритм работы функции:
 * 1. Проверяет переданный параметр на NULL.
 *  1.1 Если NULL, то возвращает управление.
 * 2. Генерирует рандомное количество продуктов в конкретном диапазоне.
 * 3. Инициализирует мьютекс и проверяет, что функция инициализации мьютекса
 * вернула 0 <- успешная инициализация.
 * 
 * @param [in,out] store Указатель на структуру ларька.
 * На входе: адрес ларька.
 * На выходе: инициализированный ларек.
 * 
 * @return  void.
 */
void init_store(struct store* store)
{
    // 1
    if (store == NULL)
    {
        // 1.1
        printf("Ошибка: объект store - NULL!");
        return;
    }
    // 2
    store->products = (rand() % (MAX_PRODUCTS - MIN_PRODUCTS + 1)) + MIN_PRODUCTS;

    // 3
    if (pthread_mutex_init(&store->mutex, NULL) != 0)
    {
        printf("Ошибка: мьютекс не был проинициализирован!");
        return;
    }
    
    return;
}