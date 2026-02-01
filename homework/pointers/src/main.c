#include <stdio.h>
#include <string.h>

#include "../include/second.h"
#include "../include/third.h"
#include "../include/first.h"

#include "../../_auxiliary-library/algorithms/boyer_moore_search.h"

#define PFN printf("\n")

#define SIZE 10 // Размер массива в 3 задании
#define STRING_SIZE 100 // Размер строк в 4 задании

void print_welcome_message(void)
{
    PFN;
    printf("Выберите, пожалуйста, номер задания из 3 ДЗ: \n" 
            "1) Поменять значение 3 байта в числе через указатель;\n"
            "2) Посмотреть результат измененного кода (см. 3 ДЗ);\n"
            "3) Вывод элементов массива через указатель;\n"
            "4) Найти подстроку в строке и вернуть указатель на начало подстроки;\n");
    PFN;
}

void fill_in_array(int* array, int size)
{
    int current_element = 0;

    for (int i = 0; i < SIZE; i++)
    {
        printf("Введите %d элемент = ", i + 1);
        scanf("%d", &current_element);

        *(array + i) = current_element;
    }
}

int main(void)
{
    print_welcome_message();

    char user_input;

    printf("Ваш выбор: ");
    scanf("%c", &user_input);

    switch (user_input)
    {
        case '1':
        {
            change_value_of_3bytes_with_pointer();
            break;
        }
        
        case '2':
        {
            second_task();
            break;
        }
        case '3':
        {
            int array[SIZE] = { 0 };
            fill_in_array(array, SIZE);
            print_array_using_pointer(array, SIZE);
            break;
        }
        case '4':
        {
            char buffer_main_string[STRING_SIZE];
            char buffer_sub_string[STRING_SIZE];

            while (getchar() != '\n'); // очистка stdin
        
            printf("Введите строку, где мы будем искать подстроку, длиной меньше %d символов: ", STRING_SIZE);
            fgets(buffer_main_string, sizeof(buffer_main_string), stdin);
            buffer_main_string[strcspn(buffer_main_string, "\n")] = '\0';

            printf("Введите подстроку, которую мы будем искать в главной строке, длиной меньше %d символов: ", STRING_SIZE);
            fgets(buffer_sub_string, sizeof(buffer_sub_string), stdin);
            buffer_sub_string[strcspn(buffer_sub_string, "\n")] = '\0';

            char* result = boyer_moore_search(buffer_main_string, buffer_sub_string);
        
            if (result != NULL)
            {
                printf("Подстрока найдена по адресу памяти: %p\n", (void *)result);
                printf("Позиция вхождения подстроки: %ld\n", result - buffer_main_string);
            } 
            else
            {
                printf("Подстрока не найдена.\n");
            }
        
            break;
        }
        default:
            break;
    }

    return 0;
}
