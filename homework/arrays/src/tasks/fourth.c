/**
    @file fourth.c
    @brief Заполнение матрицы по спирали и ее вывод в консоль
    @author @wildyellow
    @version 1.0.0
    @date 16.12.2025
 */

/** Максимальная размерность квадратной матрицы.
    Ограничение связано с диапазоном char
 */
#define MAX_N 11

/** Минимальная размерность квадратной матрицы.
    Ограничение связано с диапазоном char
 */
#define MIN_N 1

/** Текущая размерность матрицы */
#define CURRENT_N 11

#include <stdio.h>

/** Создает квадратную матрицу размером N*N, заполняет ее нулями. Затем последовательно заполняет
    ее значениями, начиная с 1, по спирали и выводит результат в стандартный поток вывода

    @return 0 при успешном выполнении, 1 при переполнении или размерности меньше единицы, 
    иное ненулевое значение при ошибке
*/
int print_snail(void)
{
    if (CURRENT_N > MAX_N)
    {
        printf("Переполнение!\n");
        return 1;
    }

    if (CURRENT_N < MIN_N)
    {
        printf("Размерность не может быть меньше 1!\n");
        return 1;
    }
    
    char matrix[CURRENT_N][CURRENT_N] = { 0 };
    char upper_limit = 0; // верхняя граница
    char lower_limit = CURRENT_N - 1; // нижняя граница
    char left_edge = 0; // левый край
    char right_edge = CURRENT_N - 1; // правый край
    char value = 1;

    while (upper_limit <= lower_limit && left_edge <= right_edge) // Пока верх не дойдет до низа и левый край до правого
    {
        for (char j = left_edge; j <= right_edge; j++) // Заполняем строку слева направо
        {
            matrix[upper_limit][j] = value++; // upper_limit = 0, j = 0..2 (заполнили)
        }
        upper_limit++;

        for (char i = upper_limit; i <= lower_limit; i++) // Заполняем правый столбец сверху вниз
        {
            matrix[i][right_edge] = value++;
        }
        right_edge--;

        if (upper_limit <= lower_limit)
        {
            for (char j = right_edge; j >= left_edge; j--) // Заполняем строку справа налево
            {
                matrix[lower_limit][j] = value++;
            }
            lower_limit--;
        }

        if (left_edge <= right_edge)
        {
            for (char i = lower_limit; i >= upper_limit ; i--) // Заполняем столбец снизу верх
            {
                matrix[i][left_edge] = value++;
            }
            left_edge++;
        }
    }

    for (int i = 0; i < CURRENT_N; i++) // Вывод матрицы
        {
            for (int j = 0; j < CURRENT_N; j++) 
            {
                printf("%4d", matrix[i][j]);
            }
            printf("\n");
        }

    return 0;
}
