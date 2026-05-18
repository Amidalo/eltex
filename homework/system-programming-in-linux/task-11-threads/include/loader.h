/**
 * @file    loader.h
 * @author  amidalo
 * @date    10-Март-2026
 * 
 * @brief Интерфейс управления погрузчиком.
 */

#ifndef _LOADER_H_
#define _LOADER_H_

#include <pthread.h>
#include <market.h>
#include <unistd.h>

/**
 * @brief Объявление функции потока, выполняющего логику погрузчика.
 * 
 * @details Погрузчик завозит в ларьки по 200 продуктов, перед этим блокируя
 * мьютекс ларька, а затем уходит в сон, перед этим высвободив мьютекс.
 */
void* loader_thread(void* arg);

#endif