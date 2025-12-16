/** 
    @file second.c
    @brief Вывод массива в обратном порядке
    @author @wildyellow
    @version 1.0.0
    @date 13.12.2025
*/

#include <stdio.h>

/** 
    Выводит в консоль обратный массив
    @param[in] array Исходный массив
    @param[in] size Размер исходного массива
*/
void print_reverse_array(char* array, char size)
{
    for (char i = size - 1; i >= 0; i--)
    {
        printf("%d ", array[i]);
    }
}
