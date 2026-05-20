/**
 * @file    main.c
 * @author  amidalo
 * @date    14-Март-2026
 * 
 * @brief Реализация первого задания на каналы.
 */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * @brief Макрос MAX_MSG_LENGTH N, где N - максимальное количество
 * символов в сообщении.
 */
#define MAX_MSG_LENGTH 10

/**
 * @brief Точка входа в программу.
 * 
 * @details Алгоритм работы функции:
 * 1. Создание хранилища для двух файловых дескрипторов.
 * 2. Создание в оперативной памяти виртуального буфера. Заполнение массива
 * fd[2] двумя значениями (файловые дескрипторы).
 * 3. Создаем дочерний процесс. Теперь у потомка и у родителя есть доступ
 * к каналу.
 * 4. Закрываем ненужный дескриптор для записи у потомка. Блокируемся на 
 * функции read, тем самым ожидая сообщения в канале. После получения закрываем
 * дескриптор для чтения и выводим полученное сообщение в терминал.
 * 5. Закрываем ненужный дескриптор для чтения. Записываем сообщение в канал.
 * Закрываем дескриптор для записи. Ждем завершения работы потомка и 
 * выводим его статус работы. 
 * 
 * @note Все дескрипторы, связанные с каналом, закрыты. Канал уничтожен.
 */
int main(void)
{
    pid_t pid;
    // 1
    int fd[2]; // 0 - read ; 1 - write
    int status;

    // 2
    if (pipe(fd) == -1)
    {
        perror("\n pipe \n");
        exit(EXIT_FAILURE);
    }

    // 3
    pid = fork();

    switch (pid)
    {
        case -1:
        {
            perror("\n fork \n");
            exit(EXIT_FAILURE);
            break;
        }
        case 0: 
        {
            // 4
            close(fd[1]);

            char msg[MAX_MSG_LENGTH];
            if (read(fd[0], msg, sizeof(msg)) == -1)
            {
                perror("\n read \n");
                exit(EXIT_FAILURE);
            }
            close(fd[0]);

            printf("\n Из родительского процесса получено следующее: %s \n",
                msg);
            break;
        }    
        default:
        {
            // 5
            close(fd[0]);

            char msg[MAX_MSG_LENGTH] = "Hi!";
            if (write(fd[1], msg, sizeof(msg)) == -1)
            {
                perror("\n write \n");
                exit(EXIT_FAILURE);
            }
            close(fd[1]);

            if (wait(&status) == -1)
            {
                perror("\n wait \n");
                exit(EXIT_FAILURE);
            }
            printf("\n Статус дочернего процесса = %d \n",
                WEXITSTATUS(status));
            break;
        }
    }
    
    return 0;
}