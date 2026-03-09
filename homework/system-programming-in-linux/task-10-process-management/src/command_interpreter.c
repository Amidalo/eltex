/**
 * @file command_interpreter.c
 * @brief Реализация аналога командного интерпретатора bash
 * @author amidalo
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Максимальный размер ввода.
 */
#define MAX_INPUT_SIZE 256

/**
 * @brief Максимальное количество аргументов.
 */
#define MAX_ARGS 64

/**
 * @brief Функция для разбора командной строки на аргументы.
 * 
 * @details Алгоритм:
 * 1) Вызываем strtok(), который ищет part в input до разделителей.
 * 2) Пока есть части (part) и количество аргументов меньше положенного.
 * 3) Сохраняем part в массив аргументов, повышаем счетчик аргументов, ищем следующая часть.
 * 4) Для системного вызова execpv() последний элемент массива должен быть NULL.
 */
void parse_command(char *input, char **args)
{
    int argument_counter = 0;
    
    char *part = strtok(input, " \t\n");
    
    while (part != NULL && argument_counter < MAX_ARGS - 1) {
        args[argument_counter] = part;
        argument_counter++;
        part = strtok(NULL, " \t\n");
    }
    
    args[argument_counter] = NULL; // для execvp
}

/**
 * @brief Вход в программу.
 * 
 * @details Алгоритм:
 * 1) Считываем ввод пользователя.
 * 2) Удаляем символ новой строки в конце.
 * 3) Проверяем на пустой ввод.
 * 4) Проверяем команду выхода.
 * 5) Разбираем команду на аргументы с помощью функции parse_command().
 * 6) Создаём дочерний процесс, if -1 -> ошибка, 0 -> выполняем программу,
 * default -> ждем завершения дочернего процесса.
 */
int main(void) 
{
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;
    
    printf("\n Добро пожаловать в аналоговый командный интерпретатор bash!\n");
    printf("\n Введите 'exit', если захотите выйти.\n\n");
    
    while (1)
    {
        printf("mycustombash> ");
        fflush(stdout);
        
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }
        
        input[strcspn(input, "\n")] = '\0';
        
        if (strlen(input) == 0) {
            continue;
        }
        
        if (strcmp(input, "exit") == 0) {
            printf("\n Вы решили выйти. \n");
            break;
        }
        
        parse_command(input, args);
        
        pid = fork();

        switch (pid)
        {
            case -1:
            {
                perror("Ошибка при создании процесса");
                break;
            }
            case 0:
            {
                if (execvp(args[0], args) == -1) 
                {
                    fprintf(stderr, "Ошибка: не удалось выполнить команду '%s'\n", args[0]);
                    exit(EXIT_FAILURE);
                }
                break;
            }
            default:
            {
                wait(&status);
                printf("Вызванная программа завершилась c кодом %d\n", WEXITSTATUS(status));
                break;
            }
        }
    }
    
    return 0;
}