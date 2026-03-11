#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(void)
{
    char buffer[BUFFER_SIZE] = "String from file";
    size_t len = strlen(buffer);

    char output_buffer[BUFFER_SIZE] = {0};

    int fd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        perror("\n Ошибка открытия файла! \n");
        return 1;
    }

    write(fd, buffer, len);
    
    lseek(fd, 0, SEEK_SET);
    
    ssize_t number_of_bytes_read = read(fd, output_buffer, BUFFER_SIZE - 1);

    if (number_of_bytes_read <= 0)
    {
        printf("Файл пустой!");
        close(fd);

        return 0;
    }
    output_buffer[number_of_bytes_read] = '\0';
    
    for (int i = number_of_bytes_read - 1; i >= 0; i--)
    {
        printf("%c", output_buffer[i]);
    }
    printf("\n");

    close(fd);

    return 0;
}