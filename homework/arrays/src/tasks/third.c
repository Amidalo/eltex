/** 
    @file thrid.c
    @brief Заполнение верхнего треугольника матрицы 0, а нижний 1
    @author @wildyellow
    @version 1.0.0
    @date 13.12.2025
*/

/** Минимальная размерность квадратной матрицы. */
#define MIN_N 1

/** Текущая размерность квадратной матрицы */
#define CURRENT_N 12

#include <stdio.h>

/** Функция проходит по каждому элементу в матрице
    и проверяет: если сумма индексов i, j элемента больше/равно двум,
    то присваивается единица, иначе остается нуль

    Пояснение: единицы стоят там, где сумма индексов элемента больше больше/равно двум

    @return 0 при успешном выполнении, либо 1, если размерность меньше 1
*/
int print_triangle_matrix()
{
    if (CURRENT_N < MIN_N)
    {
        printf("Размерность не может быть меньше 1!\n");
        return 1;
    }

    char matrix[CURRENT_N][CURRENT_N] = { 0 }; 

    for (char i = 0; i < CURRENT_N; i++)
    {
        for (char j = 0; j < CURRENT_N; j++)
        {
            if (i + j >= CURRENT_N - 1)
            {
                matrix[i][j] = 1;
                printf("%d ", matrix[i][j]);
            } else {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}