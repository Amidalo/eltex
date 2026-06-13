/**
 * @file    local_dgram_server.c
 * @author  amidalo
 * @date    01.06.26
 * @brief   AF_LOCAL SOCK_DGRAM сервер для локального взаимодействия.
 * 
 * @details Программа реализует сервер семейства AF_LOCAL с типом SOCK_DGRAM.
 * Сервер обеспечивает датаграммное (без установки соединения)
 * взаимодействие. Сервер привязывается к адресу, принимает сообщение
 * от клиента, отправляет ответ и завершает работу.
 */

#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Точка входа AF_LOCAL SOCK_DGRAM сервера.
 * 
 * @details Алгоритм AF_LOCAL SOCK_DGRAM сервера:
 * 1. Создание сокета и резервирование дескриптора под него.
 * 2. Инициализация структуры sockaddr_un server,
 * _un указывает на то, что эндпоинт - путь к файлу, локальная область
 * применения. Проверка на существование файла, если был -> удалить.
 * 3. Привязка нашего эндпоинта к конкретному адресу (имени).
 * 4. Прием данных от клиента с помощью recvfrom().
 * Вывод полученного сообщения на экран.
 * 5. Отправка ответного сообщения клиенту с помощью sendto(),
 * используя полученный адрес клиента.
 * 6. Удаление файла сокета. Закрытие сокета и завершение работы.
 * 
 * @return int Возвращает 0 при успешном завершении, EXIT_FAILURE при ошибке
 */
int main(void)
{
    // 1.
    int fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        perror("socket server");
        exit(EXIT_FAILURE);                
    }

    // 2.
    struct sockaddr_un server, client;
    char *path = "./local_dgram";
    if (access(path, F_OK) == 0)
    {
        if (unlink(path) == -1)
        {
            perror("unlink");
            close(fd);
            exit(EXIT_FAILURE);
        }
        
    }
    
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, path, sizeof(server.sun_path));

    // 3.
    if(bind(fd, (struct sockaddr*)&server, sizeof(struct sockaddr_un)) == -1)
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

    ssize_t nbytes = recvfrom(
        fd,
        (void*)buffer_recv, 
        sizeof(buffer_recv) - 1, 
        0, 
        (struct sockaddr*)&client, 
        &size_client
    ); 
    if (nbytes == -1)
    {
        perror("recvfrom server");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer_recv[nbytes] = '\0';
    printf("AF_LOCAL SOCK_DGRAM сервер получил: %s\n", buffer_recv);
    
    // 5.
    if(sendto(
        fd, 
        (void*)buffer_send, strlen(buffer_send), 
        0, 
        (struct sockaddr*)&client, size_client) == -1
    ) {
        perror("sendto server");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 6.
    if (unlink(path) == -1)
    {
        perror("unlink");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    return 0;
}