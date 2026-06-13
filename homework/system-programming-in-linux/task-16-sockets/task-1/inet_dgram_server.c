/**
 * @file    inet_dgram_server.c
 * @author  amidalo
 * @date    01.06.26
 * @brief   AF_INET SOCK_DGRAM сервер для сетевого взаимодействия по UDP.
 * 
 * @details Программа реализует сервер семейства AF_INET (IPv4) с типом SOCK_DGRAM (UDP).
 * Сервер обеспечивает датаграммное (без установки соединения)
 * взаимодействие через сеть. Сервер привязывается к порту 7777,
 * принимает сообщение от клиента, отправляет ответ и завершает работу.
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Точка входа AF_INET SOCK_DGRAM сервера.
 * 
 * @details Алгоритм AF_INET SOCK_DGRAM сервера:
 * 1. Создание сокета и резервирование дескриптора под него.
 * 2. Инициализация структуры sockaddr_in server: установка семейства AF_INET,
 * преобразование порта 7777 в сетевой порядок байт с помощью htons(),
 * преобразование IP-адреса "127.0.0.1" в двоичный формат с помощью inet_pton().
 * 3. Привязка сокета к адресу и порту.
 * 4. Прием данных от клиента с помощью recvfrom(), который также возвращает
 * адрес отправителя (клиента). Вывод полученного сообщения на экран.
 * 5. Отправка ответного сообщения клиенту с помощью sendto(),
 * используя полученный адрес клиента.
 * 
 * @return int Возвращает 0 при успешном завершении, EXIT_FAILURE при ошибке
 */
int main(void)
{
    // 1.
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
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
    socklen_t size_client;
    size_client = sizeof(client);
    char buffer_send[] = "Hi!";
    char buffer_recv[8] = { 0 };

    ssize_t nbytes_recvfrom = recvfrom(
        fd, 
        (void*)buffer_recv, 
        sizeof(buffer_recv) - 1, 
        0, 
        (struct sockaddr*)&client, &size_client
    );
    if (nbytes_recvfrom == -1)
    {
        perror("recvfrom server");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer_recv[nbytes_recvfrom] = '\0';
    printf("AF_INET SOCK_DGRAM сервер получил: %s\n", buffer_recv);

    // 5.
    if(sendto(
        fd, 
        (void*)buffer_send, 
        strlen(buffer_send), 0, 
        (struct sockaddr*)&client, size_client) == -1
    ) {
        perror("sendto server");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    return 0;
}