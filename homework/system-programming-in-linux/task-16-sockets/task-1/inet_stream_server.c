/**
 * @file    inet_stream_server.c
 * @author  amidalo
 * @date    01.06.26
 * @brief   AF_INET SOCK_STREAM сервер для сетевого взаимодействия по TCP.
 * 
 * @details Программа реализует сервер семейства AF_INET (IPv4) с типом SOCK_STREAM (TCP).
 * Сервер обеспечивает надежное потоковое соединение через сеть.
 * Сервер ожидает подключения клиента на порту 7777, принимает от него сообщение,
 * отправляет ответ и завершает работу.
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Точка входа AF_INET SOCK_STREAM сервера.
 * 
 * @details Алгоритм AF_INET SOCK_STREAM сервера:
 * 1. Создание сокета и резервирование дескриптора под него.
 * 2. Инициализация структуры sockaddr_in server: установка семейства AF_INET,
 * преобразование порта 7777 в сетевой порядок байт с помощью htons(),
 * преобразование IP-адреса "127.0.0.1" в двоичный формат с помощью inet_pton().
 * 3. Привязка сокета к адресу и порту.
 * 4. Перевод сокета в пассивный режим для ожидания подключений (listen).
 * 5. Установка соединения. accept() блокирует выполнение до подключения клиента
 * и возвращает новый файловый дескриптор для обмена данными.
 * 6. Прием данных от клиента с помощью recv() и вывод их на экран.
 * 7. Отправка ответного сообщения клиенту с помощью send().
 * 8. Закрытие клиентского и серверного сокетов, завершение работы.
 * 
 * @return int Возвращает 0 при успешном завершении, EXIT_FAILURE при ошибке
 */
int main(void)
{
    // 1.
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket server");
        exit(EXIT_FAILURE);                
    }

    // 2.
    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_port = htons(7777);
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0)
    {
        perror("inet_pton server");
        close(fd);
        exit(EXIT_FAILURE); 
    }
    
    // 3.
    if (bind(fd, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) == -1)
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
    socklen_t client_len;
    int new_fd = accept(fd, (struct sockaddr*)&client, &client_len);
    if (new_fd == -1)
    {
        perror("accept server");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char buffer_send[] = "Hi!";
    char buffer_recv[8] = { 0 };

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
        close(fd);
        close(new_fd);
        exit(EXIT_FAILURE);
    }
    buffer_recv[nbytes_recv] = '\0';
    printf("AF_INET SOCK_STREAM сервер получил: %s\n", buffer_recv);
    
    // 7.
    if(send(new_fd, (void*)buffer_send, strlen(buffer_send), 0) == -1)
    {
        perror("send server");
        close(fd);
        close(new_fd);
        exit(EXIT_FAILURE);
    }

    // 8.
    close(new_fd);
    close(fd);

    return 0;
}