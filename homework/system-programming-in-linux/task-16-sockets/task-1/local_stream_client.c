/**
 * @file    local_stream_client.c
 * @author  amidalo
 * @date    01.06.26
 * @brief   AF_LOCAL SOCK_STREAM клиент для локального взаимодействия.
 * 
 * @details Программа реализует клиент семейства AF_LOCAL с типом SOCK_STREAM.
 * Клиент обеспечивает потоковое соединение с сервером.
 * Клиент подключается к серверу, отправляет сообщение, получает ответ
 * и завершает работу.
 */

#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Точка входа AF_LOCAL SOCK_STREAM клиента.
 * 
 * @details Алгоритм AF_LOCAL SOCK_STREAM клиента:
 * 1. Создание сокета и резервирование дескриптора под него.
 * 2. Инициализация структуры sockaddr_un server,
 * _un указывает на то, что эндпоинт - путь к файлу, локальная область
 * применения.
 * 3. Установка соединения с сервером через connect().
 * 4. Отправка сообщения серверу с помощью send().
 * 5. Прием ответного сообщения от сервера с помощью recv().
 * Вывод полученного сообщения на экран.
 * 6. Закрытие сокета и завершение работы.
 * 
 * @return int Возвращает 0 при успешном завершении, EXIT_FAILURE при ошибке
 */
int main(void)
{
    // 1.
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket client");
        exit(EXIT_FAILURE);                
    }

    // 2.
    struct sockaddr_un server;
    char *path = "./local_stream";
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, path, sizeof(server.sun_path));

    // 3.
    if (connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr_un)) == -1)
    {
        perror("connect");
        close(fd);
        exit(EXIT_FAILURE); 
    }
    
    char buffer_send[] = "Hello!";
    char buffer_recv[8];

    // 4.
    if (send(fd, (void*)buffer_send, strlen(buffer_send), 0) == -1)
    {
        perror("send client");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    // 5.
    ssize_t nbytes_recv = recv(
        fd, 
        (void*)buffer_recv, 
        sizeof(buffer_recv) - 1, 
        0
    );
    if (nbytes_recv == -1)
    {
        perror("recv server");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer_recv[nbytes_recv] = '\0';
    printf("AF_LOCAL SOCK_STREAM клиент получил: %s\n", buffer_recv);

    // 6.
    close(fd);

    return 0;
}