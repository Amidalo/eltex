/**
 * @file server.c
 * @author amidalo
 * @date 14-Март-2026
 * 
 * @details Реализация сервера для демонстрации именованного канала.
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

/**
 * @brief Точка входа в программу.
 * 
 * @details Алгоритм работы программы:
 * 1. Инициализируем специализированный файла, по имени которого сервер
 * сможет найти буфер.
 * 2. Открываем файл на запись и блокируемся на этом open, ожидая подключения
 * клиента, который откроет этот же файл на чтение O_RDONLY.
 * 3. Записываем наше сообщение в канал.
 * 4. Закрываем файловый дескриптор.
 */
int main(void)
{
    char* path = "./fifo";

    if (access(path, F_OK) == 0)
    {
        if (remove(path) != 0)
        {
            perror("remove");
            exit(EXIT_FAILURE);
        }
    }

    char msg[] = "Hi!";

    // 1
    if (mkfifo(path, 0644) == -1)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // 2
    int fd = open(path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 3
    if (write(fd, msg, strlen(msg) + 1) == -1)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    printf("C сервера отправлено: %s\n", msg);

    // 4
    close(fd);

    return 0;
}
