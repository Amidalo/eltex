/**
 * @file command_interpreter_pro_max.c
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
 * @brief Реализация функции, проверяющая наличие неименованного канала -> |.
 * 
 * @details Алгоритм работы функции:
 * 1. Проверка переданных параметров на NULL.
 * 2. Проверяем в input наличие символа '|' с помощью strchr().
 * 3. Если указатель NULL -> неименованного канала нет.
 * 4. Есть указатель не NULL, то делим input на правую и левую части.
 * 
 * @param [in,out] input Указатель на буфер
 */
int detect_pipe_line(char* input, char** left, char** right)
{
    // 1
    if (input == NULL)
    {
        perror("input is NULL");
        exit(EXIT_FAILURE);
    }
    if (left == NULL)
    {
        perror("left pointer is NULL");
        exit(EXIT_FAILURE);
    }
    if (right == NULL)
    {
        perror("right pointer is NULL");
        exit(EXIT_FAILURE);
    }

    // 2
    char* pipe_line_p = strchr(input, '|');

    // 3
    if (pipe_line_p == NULL)
    {
        return 0;
    }

    // 4
    *pipe_line_p = '\0';
    *left = input;
    *right = pipe_line_p + 1;

    return 1;
}

/**
 * @brief Функция для разбора командной строки на аргументы.
 * 
 * @details Алгоритм:
 * 1) Вызываем strtok(), который ищет part в input до разделителей.
 * 2) Пока есть части (part) и количество аргументов меньше положенного.
 * 3) Сохраняем part в массив аргументов, повышаем счетчик аргументов, ищем следующая часть.
 * 4) Для системного вызова execvp() последний элемент массива должен быть NULL.
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
 * 1. Если detect_pipe_line() обнаружила '|':
 *  1.1 Разбираем левую и правую части на аргументы с 
 *  помощью функции parse_command().
 *  1.2 Создаем массив дескрипторов и неименованный канал.
 *  1.3 Потомок левой части с помощью dup2 копирует дескриптор fd[1]
 *  в дескриптор с номером 1 (stdout -> все данные выводятся не на экран, а
 *  в канал). Закрываем fd[1], так как он больше без надобности.
 *  Выполняем программу.
 *  1.4 Потомок правой части с помощью dup2 копирует дескриптор fd[0]
 *  в дескриптор с номером 0 (stdin -> все данные читаются не с клавиатруы, а
 *  с канала). Закрываем fd[0], так как он больше без надобности.
 *  Выполняем программу.
 *  1.5 Не забываем закрыть в родителе дескрипторы для уничтожения канала.
 * 
 * 2. Если detect_pipe_line() не обнаружила '|':
 *  2.1 Разбираем команду на аргументы с помощью функции parse_command().
 *  2.2 Создаём дочерний процесс, if -1 -> ошибка, 0 -> выполняем программу,
 *  default -> ждем завершения дочернего процесса.
 */
int main(void) 
{
    char input[MAX_INPUT_SIZE];
    char *args_left[MAX_ARGS], *args_right[MAX_ARGS];
    pid_t pid_left, pid_right;
    int status;
    
    printf("\n Добро пожаловать в аналоговый командный интерпретатор bash pro max!\n");
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

        char* left;
        char* right;

        // 1
        if (detect_pipe_line(input, &left, &right))
        {
            // 1.1
            parse_command(left, args_left);
            parse_command(right, args_right);

            // 1.2
            int fd[2];
            if (pipe(fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            // 1.3
            pid_left = fork();
            switch (pid_left)
            {
                case -1:
                {
                    perror("Ошибка при создании дочернего процесса");
                    break;
                }
                case 0:
                {
                    dup2(fd[1], 1);
                    close(fd[0]);
                    close(fd[1]);

                    if (execvp(args_left[0], args_left) == -1)
                    {
                        fprintf(stderr, "Ошибка: не удалось выполнить команду '%s'\n",
                            args_left[0]);
                        exit(EXIT_FAILURE);
                    }
                
                    break;
                }
            }

            // 1.4
            pid_right = fork();
            switch (pid_right)
            {
                case -1:
                {
                    perror("Ошибка при создании дочернего процесса");
                    break;
                }
                case 0:
                {
                    dup2(fd[0], 0);
                    close(fd[1]);
                    close(fd[0]);

                    if (execvp(args_right[0], args_right) == -1)
                    {
                        fprintf(stderr, "Ошибка: не удалось выполнить команду '%s'\n",
                            args_right[0]);
                        exit(EXIT_FAILURE);
                    }
                    break;
                }
            }

            // 1.5
            close(fd[0]);
            close(fd[1]);

            waitpid(pid_left, &status, 0);
            waitpid(pid_right, &status, 0);
        }
        // 2
        else
        {
            left = input;
            // 2.1
            parse_command(left, args_left);

            /// 2.2
            pid_left = fork();

            switch (pid_left)
            {
                case -1:
                {
                    perror("Ошибка при создании процесса");
                    break;
                }
                case 0:
                {
                    if (execvp(args_left[0], args_left) == -1) 
                    {
                        fprintf(stderr, "Ошибка: не удалось выполнить команду '%s'\n",
                            args_left[0]);
                        exit(EXIT_FAILURE);
                    }
                    break;
                }
                default:
                {
                    wait(&status);
                    printf("Вызванная программа завершилась c кодом %d\n",
                        WEXITSTATUS(status));
                    break;
                }
            }
        }
    }
    
    return 0;
}