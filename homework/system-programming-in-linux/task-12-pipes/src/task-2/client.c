/**
 * @file client.c
 * @author amidalo
 * @date 14-Март-2026
 * 
 * @details Реализация клиента для демонстрации именованного канала.
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

/**
 * @brief Макрос BUF_SIZE N, где N - размер принимающего буфера.
 */
#define BUF_SIZE 256

/**
 * @brief Точка входа в программу.
 * 
 * @details Алгоритм работы программы:
 * 1. Открываем спец. файл, созданный сервером, на чтение.
 * 2. Читаем из канала и добавляем null terminator.
 * 3. Закрываем файловый дескриптор и удаляем файл.
 */
int main(void)
{
    char* path = "./fifo";
    char buf[BUF_SIZE];

    // 1
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 2
    ssize_t nbytes = read(fd, buf, BUF_SIZE - 1);
    if (nbytes == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    else if (nbytes == 0)
    {
        printf("EOF\n");
        close(fd);
        return 0;
    }

    buf[nbytes] = '\0';
    printf("C сервера получено: %s\n", buf);

    // 3
    close(fd);

    if (remove(path) != 0)
    {
        perror("remove");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
