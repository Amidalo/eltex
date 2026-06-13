/**
 * @file    task_1_first_program.c
 * @author  amidalo
 * @date    27.05.26
 * @brief   Программа переопределения диспозиции сигнала SIGUSR1.
 * 
 * @details Программа демонстрирует переопределение диспозиции сигнала SIGUSR1
 * с помощью вызова sigaction(). Программа устанавливает собственный
 * обработчик сигнала, после чего уходит в бесконечный цикл ожидания.
 * При получении сигнала SIGUSR1 на экран выводится сообщение.
 * PID процесса выводится для возможности отправки сигнала через kill().
 */

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Обработчик сигнала SIGUSR1.
 * 
 * @details Функция вызывается при получении сигнала SIGUSR1.
 * Выводит на экран сообщение о получении сигнала.
 * 
 * @param sig Номер полученного сигнала (ожидается SIGUSR1)
 */
void handler(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("Сигнал SIGUSR1 получен!\n");
    }

    return;
}

/**
 * @brief Точка входа программы-перехватчика сигналов.
 * 
 * @details Алгоритм программы:
 * 1. Инициализация структуры struct sigaction.
 * Установка обработчика сигнала handler в поле sa_handler.
 * Очистка маски сигналов и добавление SIGUSR1 в маску блокируемых
 * сигналов на время выполнения обработчика.
 * 2. Вызов sigaction() для переопределения диспозиции сигнала SIGUSR1.
 * 3. Вывод PID процесса на экран для возможности отправки сигнала.
 * 4. Бесконечный цикл ожидания сигнала с помощью pause().
 * 
 * @return int Возвращает 0 при успешном завершении, EXIT_FAILURE при ошибке
 */
int main(void)
{
    // 1.
    struct sigaction action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask, SIGUSR1);
    action.sa_flags = 0;

    // 2.
    if (sigaction(SIGUSR1, &action, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // 3.
    printf("PID: %d, waiting for SIGUSR1\n", getpid());

    // 4.
    while (1)
    {
        pause();
    }

    return 0;
}