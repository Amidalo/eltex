/**
 * @file    local_dgram_client.c
 * @author  amidalo
 * @date    01.06.26
 * @brief   AF_LOCAL SOCK_DGRAM клиент для локального взаимодействия.
 * 
 * @details Программа реализует клиент семейства AF_LOCAL с типом SOCK_DGRAM.
 * Клиент обеспечивает датаграммное (без установки соединения)
 * взаимодействие. Клиент создает собственный адрес (файл сокета),
 * подключается к серверу, отправляет сообщение, получает ответ
 * и завершает работу.
 */

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>

/**
 * @brief Точка входа AF_LOCAL SOCK_DGRAM клиента.
 * 
 * @details Алгоритм AF_LOCAL SOCK_DGRAM клиента:
 * 1. Создание сокета и резервирование дескриптора под него.
 * 2. Инициализация структуры sockaddr_un client для собственного адреса клиента.
 * Удаление файла сокета, если он уже существует. Привязка адреса к сокету,
 * чтобы сервер знал, куда отправлять ответ.
 * 3. Инициализация структуры sockaddr_un server с адресом сервера.
 * 4. Установка соединения с сервером через connect().
 * Для SOCK_DGRAM connect() фиксирует адрес получателя по умолчанию.
 * 5. Создание буферов для отправки и приема данных.
 * 6. Отправка сообщения серверу с помощью send().
 * 7. Прием ответного сообщения от сервера с помощью recv().
 * Вывод полученного сообщения на экран.
 * 8. Закрытие сокета и завершение работы.
 * 
 * @note В локальных UDP-сокетах автоматическая привязка к файлу не происходит. 
 * Если клиент перед отправкой не вызвал bind(), сервер получает пустой адрес клиента. 
 * Попытка отправить ответ на пустой адрес вызывает эту ошибку.
 * 
 * @return int Возвращает 0 при успешном завершении, EXIT_FAILURE при ошибке
 */
int main(void)
{
    // 1.
    int fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        perror("socket client");
        exit(EXIT_FAILURE);        
    }

    // 2.
    struct sockaddr_un client;
    client.sun_family = AF_LOCAL;
    char *client_path = "./local_dgram_client";
    unlink(client_path);
    strncpy(client.sun_path, client_path, sizeof(client.sun_path));

    if (bind(fd, (struct sockaddr*)&client, sizeof(struct sockaddr_un)) == -1)
    {
        perror("bind client");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 3.
    struct sockaddr_un server;
    server.sun_family = AF_LOCAL;
    char *path = "./local_dgram";
    strncpy(server.sun_path, path, sizeof(server.sun_path));

    // 4.
    if (connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr_un)) == -1)
    {
        perror("connect");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    // 5.
    char buffer_send[] = "Hello!";
    char buffer_recv[8] = { 0 };

    // 6.
    ssize_t nbytes_sent = send(fd, (void*)buffer_send, strlen(buffer_send), 0);
    if (nbytes_sent == -1)
    {
        perror("send");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    // 7.
    ssize_t nbytes_received = recv(fd, (void*)buffer_recv, sizeof(buffer_recv) - 1, 0);
    if (nbytes_received == -1)
    {
        perror("recv");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer_recv[nbytes_received] = '\0';
    printf("AF_LOCAL SOCK_DGRAM клиент получил: %s\n", buffer_recv);
    
    // 8.
    close(fd);

    return 0;
}