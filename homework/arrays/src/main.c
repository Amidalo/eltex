#include <stdio.h>
#include <limits.h>
#include "../include/first.h"
#include "../include/second.h"
#include "../include/third.h"
#include "../include/fourth.h"

/** Размерность массива во втором задании */
#define N 5

/** 
    @brief Точка входа в программу

    Пользователь может выбирать один из пунктов без надобности каждый раз запускать программу:
    1) Заполнение квадратной матрицы значениями от 1 до N^2 и вывод её на экран;
    2) Вывод массива в обратном порядке;
    3) Вывод треугольной матрицы (0 поверх побочной диагонали, остальные 1);
    4) Вывод улитки;
    5) Выход.

    @return 0 при успешном выполнении
*/
int main(void)
{
    printf("\n Приветствую во втором домашнем задании! Выберите задачу:");

    while (1)
    {
        printf("\n 1) Заполнение квадратной матрицы значениями от 1 до N^2 и вывод её на экран;"
               "\n 2) Вывод массива в обратном порядке;"
               "\n 3) Вывод треугольной матрицы (0 поверх побочной диагонали, остальные 1);"
               "\n 4) Вывод улитки;"
               "\n 5) Выход.");
    
        char user_input = 0;

        printf("\n Выберите пункт: ");
        scanf(" %c", &user_input);

        switch (user_input)
        {
        case '1':
            print_matrix_1toN2();
            printf("\n Примечание: поменять значение макроса CURRENT_N (размерность) можно внутри файла first.c\n");
            break;

        case '2':
            char array[N] = { 0 };
            char result = 0; // для проверки ввода ввода
            int temp = 0; // для проверки диапазона char
            printf("\n Введите %d элементов для массива (диапазон char %d до %d):\n", N, CHAR_MIN, CHAR_MAX);

            for (char i = 0; i < N; i++)
            {
                printf("%d элемент = ", i);
                result = scanf(" %d", &temp);
                if (result != 1)
                {
                    printf("\n Неверный ввод! ");
                    i--;

                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    continue;
                }

                if (temp < CHAR_MIN || temp > CHAR_MAX)
                {
                    printf("\n Вы вышли за диапазон char (-128 -- 127)");
                    i--;
                    continue;
                }
                array[i] = (char)temp;
            }
            print_reverse_array(array, N);

            printf("\n Примечание: поменять значение макроса N (размерность) можно внутри файла main.c\n");
            break;

        case '3':
            print_triangle_matrix();
            printf("\n Примечание: поменять значение макроса CURRENT_N (размерность) можно внутри файла third.c\n");
            break;

        case '4':
            print_snail();
            printf("\n Примечание: поменять значение макроса CURRENT_N (размерность) можно внутри файла fourth.c\n");
            break;

        case '5':
            printf("\n Вы решили выйти.\n");
            return 0;

        default:
            printf("\n Такого пункта нет. Попробуйте еще раз!\n");
            break;
        }
    }
}