/**
 * @file    local_stream_server.c
 * @author  amidalo
 * @date    01.06.26
 * @brief   AF_LOCAL SOCK_STREAM сервер для локального взаимодействия.
 * 
 * @details Программа реализует сервер семейства AF_LOCAL с типом SOCK_STREAM.
 * Сервер обеспечивает потоковое соединение.
 * Сервер ожидает подключения клиента, принимает от него сообщение,
 * отправляет ответ и завершает работу.
 */

#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * @brief Точка входа AF_LOCAL SOCK_STREAM сервера.
 * 
 * @details Алгоритм AF_LOCAL SOCK_STREAM сервера:
 * 1. Создание сокета и резервирование дескриптора под него.
 * 2. Инициализация структуры sockaddr_un server,
 * _un указывает на то, что эндпоинт - путь к файлу, локальная область
 * применения. Проверка на существование файла, если был -> удалить.
 * 3. Привязка нашего эндпоинта к конкретному адресу (имени), чтобы начать обмен.
 * 4. Перевод сокета в пассивный режим через зарезервированный под него
 * файловый дескриптор.
 * 5. Установка соединения. Ждем, пока клиент не сделает connect(). 
 * accept() вернет нам новый файловый дескриптор для чтения/передачи данных.
 * 6. Прием данных от клиента с помощью recv() и вывод их на экран.
 * 7. Отправка ответного сообщения клиенту с помощью send().
 * 8. Удаление файла. Закрытие сокетов (клиентского и серверного) 
 * и завершение работы.
 * 
 * @return int Возвращает 0 при успешном завершении, EXIT_FAILURE при ошибке.
 */
int main(void)
{
    // 1.
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket server");
        exit(EXIT_FAILURE);                
    }

    // 2.
    struct sockaddr_un server /*client*/;
    char *path = "./local_stream";
    if (access(path, F_OK) == 0)
    {
        if(unlink(path) == -1)
        {
            perror("unlink");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, path, sizeof(server.sun_path));

    // socklen_t client_len;

    // 3.
    if (bind(fd, (struct sockaddr*)&server, sizeof(struct sockaddr_un)) == -1)
    {
        perror("bind server");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 4.
    if (listen(fd, 1) == -1)
    {
        perror("listen server");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 5.
    int new_fd = accept(fd, NULL/*(struct sockaddr*)&client*/, NULL/*&client_len*/);
    if (new_fd == -1)
    {
        perror("listen server");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char buffer_send[] = "Hi!";
    char buffer_recv[8];

    // 6.
    ssize_t nbytes_recv = recv(
        new_fd, 
        (void*)buffer_recv, 
        sizeof(buffer_recv) - 1, 
        0
    );
    if (nbytes_recv == -1)
    {
        perror("recv server");
        close(new_fd);
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer_recv[nbytes_recv] = '\0';
    printf("AF_LOCAL SOCK_STREAM сервер получил: %s\n", buffer_recv);

    // 7.
    if (send(new_fd, (void*)buffer_send, strlen(buffer_send), 0) == -1)
    {
        perror("send server");
        close(new_fd);
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 8.
    unlink(path);
    close(new_fd);
    close(fd);

    return 0;
}