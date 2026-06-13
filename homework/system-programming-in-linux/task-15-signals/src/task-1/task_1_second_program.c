/**
 * @file    task_1_second_program.c
 * @author  amidalo
 * @date    27.05.26
 * @brief   Программа отправки сигнала SIGUSR1 процессу.
 * 
 * @details Программа демонстрирует отправку сигнала SIGUSR1 другому процессу
 * с помощью системного вызова kill(). Программа принимает в качестве
 * аргумента командной строки PID целевого процесса и отправляет ему
 * сигнал SIGUSR1. Также сигнал можно отправить с помощью утилиты kill.
 */

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * @brief Точка входа программы-отправителя сигнала.
 * 
 * @details Алгоритм программы:
 * 1. Проверка количества аргументов командной строки.
 * Программа ожидает ровно один аргумент - PID целевого процесса.
 * 2. Преобразование строкового аргумента в числовой PID с помощью atoi().
 * 3. Отправка сигнала SIGUSR1 процессу с указанным PID с помощью kill().
 * 4. Вывод сообщения об успешной отправке сигнала.
 * 
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки (argv[1] - PID процесса)
 * 
 * @return int Возвращает 0 при успешном завершении, 1 при ошибке в аргументах,
 *             EXIT_FAILURE при ошибке отправки сигнала
 */
int main(int argc, char const *argv[])
{
    // 1.
    if (argc != 2)
    {
        printf("1 arg is a program's name, 2 arg is a pid\n");
        return 1;
    }
    
    // 2.
    pid_t pid = (pid_t)atoi(argv[1]);

    // 3.
    if (kill(pid, SIGUSR1) == -1)
    {
        perror("kill\n");
        exit(EXIT_FAILURE);
    }

    // 4.
    printf("Сигнал был отправлен!\n");
    
    return 0;
}