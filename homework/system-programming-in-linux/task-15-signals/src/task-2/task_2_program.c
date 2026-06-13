/**
 * @file    task_2_program.c
 * @author  amidalo
 * @date    27.05.26
 * @brief   Программа блокировки сигнала SIGINT.
 * 
 * @details Программа демонстрирует блокировку сигнала SIGINT с помощью вызова
 * sigprocmask(). После блокировки сигнала программа уходит в бесконечный
 * цикл ожидания. Сигнал SIGINT (Ctrl+C) не будет обработан и останется
 * в очереди сигналов до разблокировки или завершения программы.
 * Для проверки используется программа отправки сигналов из задания 1
 * или утилита kill.
 */

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Точка входа программы блокировки сигналов.
 * 
 * @details Алгоритм программы:
 * 1. Инициализация набора сигналов (sigset_t).
 * Очистка набора сигналов с помощью sigemptyset().
 * Добавление сигнала SIGINT в набор с помощью sigaddset().
 * 2. Блокировка сигнала SIGINT с помощью sigprocmask() с флагом SIG_BLOCK.
 * 3. Вывод PID процесса на экран для возможности отправки сигнала.
 * 4. Бесконечный цикл ожидания с помощью pause().
 * 
 * Примечание: SIGINT - сигнал прерывания, обычно генерируется при нажатии Ctrl+C.
 * После блокировки сигнал не будет доставлен процессу и останется в очереди.
 * 
 * @return int Возвращает 0 при успешном завершении, EXIT_FAILURE при ошибке
 */
int main(void)
{
    // 1.
    sigset_t sa_mask;

    sigemptyset(&sa_mask);
    sigaddset(&sa_mask, SIGINT);

    // 2.
    if (sigprocmask(SIG_BLOCK, &sa_mask, NULL) == -1)
    {
        perror("sigprocmask\n");
        exit(EXIT_FAILURE);
    }

    // 3.
    printf("PID: %d, SIGINT is blocked\n", getpid());

    // 4.
    while (1)
    {
        pause();
    }
    
    return 0;
}