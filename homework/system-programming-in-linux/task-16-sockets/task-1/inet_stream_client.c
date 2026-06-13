/**
 * @file    inet_stream_client.c
 * @author  amidalo
 * @date    01.06.26
 * @brief   AF_INET SOCK_STREAM клиент для сетевого взаимодействия по TCP.
 * 
 * @details Программа реализует клиент семейства AF_INET (IPv4) с типом SOCK_STREAM (TCP).
 * Клиент обеспечивает надежное потоковое соединение через сеть.
 * Клиент подключается к серверу на порт 7777 локального хоста,
 * отправляет сообщение, получает ответ и завершает работу.
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Точка входа AF_INET SOCK_STREAM клиента.
 * 
 * @details Алгоритм AF_INET SOCK_STREAM клиента:
 * 1. Создание сокета и резервирование дескриптора под него.
 * 2. Инициализация структуры sockaddr_in server: установка семейства AF_INET,
 * преобразование порта 7777 в сетевой порядок байт с помощью htons(),
 * преобразование IP-адреса "127.0.0.1" в двоичный формат с помощью inet_pton().
 * 3. Установка соединения с сервером через connect().
 * 4. Отправка сообщения серверу с помощью send().
 * 5. Прием ответного сообщения от сервера с помощью recv().
 * 6. Закрытие сокета и завершение работы.
 * 
 * @return int Возвращает 0 при успешном завершении, EXIT_FAILURE при ошибке
 */
int main(void)
{
    // 1.
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket client");
        exit(EXIT_FAILURE);                
    }

    // 2.
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(7777);
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0)
    {
        perror("inet_pton client");
        close(fd);
        exit(EXIT_FAILURE); 
    }

    // 3.
    if (connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) == -1)
    {
        perror("connect client");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char buffer_send[] = "Hello!";
    char buffer_recv[8] = { 0 };

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
        perror("recv client");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer_recv[nbytes_recv] = '\0';
    printf("AF_INET SOCK_STREAM клиент получил: %s\n", buffer_recv);

    // 6.
    close(fd);

    return 0;
}