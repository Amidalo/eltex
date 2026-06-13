/**
 * @file    task_3_program.c
 * @author  amidalo
 * @date    27.05.26
 * @brief   Программа event-loop с использованием sigwait() для ожидания сигнала SIGUSR1.
 * 
 * @details Программа демонстрирует реализацию event-loop с помощью вызова sigwait().
 * При запуске программа блокирует сигнал SIGUSR1 с помощью sigprocmask()
 * и переходит в бесконечный цикл ожидания сигнала. При получении сигнала
 * SIGUSR1 на экран выводится сообщение и осуществляется переход на
 * следующую итерацию цикла.
 */

#define _POSIX_C_SOURCE 199506L

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Точка входа программы event-loop с sigwait().
 * 
 * @details Алгоритм программы:
 * 1. Инициализация набора сигналов (sigset_t) и переменной для номера сигнала.
 * Очистка набора сигналов с помощью sigemptyset().
 * Добавление сигнала SIGUSR1 в набор с помощью sigaddset().
 * 2. Блокировка сигнала SIGUSR1 с помощью sigprocmask() с флагом SIG_BLOCK.
 * Блокировка необходима, чтобы сигнал не был доставлен асинхронно,
 * а ожидал вызова sigwait().
 * 3. Вывод PID процесса на экран для возможности отправки сигнала.
 * 4. Бесконечный цикл event-loop:
 * Ожидание сигнала из набора sa_mask с помощью sigwait().
 * При успешном получении проверка номера сигнала.
 * Если получен SIGUSR1, вывод сообщения на экран.
 * Переход на следующую итерацию цикла.
 * 
 * @return int Возвращает 0 при успешном завершении, EXIT_FAILURE при ошибке
 */
int main(void)
{
    // 1.
    sigset_t sa_mask;
    int sig;

    sigemptyset(&sa_mask);
    sigaddset(&sa_mask, SIGUSR1);

    // 2.
    if (sigprocmask(SIG_BLOCK, &sa_mask, NULL) == -1)
    {
        perror("sigprocmask\n");
        exit(EXIT_FAILURE);
    }

    // 3.
    printf("PID: %d\n", getpid());

    // 4.
    while (1)
    {
        if (sigwait(&sa_mask, &sig) != 0)
        {
            perror("sigwait\n");
            exit(EXIT_FAILURE);
        }

        if (sig == SIGUSR1)
        {
            printf("Был получен сигнал SIGUSR1 через sigwait\n");
        }    
    }

    return 0;
}