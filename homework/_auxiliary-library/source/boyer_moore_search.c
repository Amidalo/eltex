#include <stdio.h>
#include <string.h>

#include "../algorithms/find_max_between_two_num.h"

#define NO_OF_CHARS 256 // Для всех символов ASCII

/**
 * Метод использует эвристику алгоритма Бойера-Мура - правило плохого символа.
 * Создается массив, который хранит в себе позицию последнего появления символа в подстроке.
 * До выявления последнего появления символа все символы помечаются -1 -> отсутствующие.
 */
void bad_char_heuristic(char* substr, int size, int badchar[NO_OF_CHARS])
{
    int32_t i;

    for (i = 0; i < NO_OF_CHARS; i++)
    {
        badchar[i] = -1;
    }

    for (i = 0; i < size; i++)
    {
        badchar[(int32_t)substr[i]] = i;
    }
}

/**
 * Метод сравнивает подстроку со строкой справла налево, начиная с конца подстроки.
 */
char* boyer_moore_search(char* str, char* substr)
{
    int32_t length_str = strlen(str);
    int32_t length_substr = strlen(substr);
    int32_t shift = 0; // сдвиг подстроки относительно строки

    if (length_substr == 0) return str;
    if (length_str < length_substr) return NULL;

    int badchar[NO_OF_CHARS];
    bad_char_heuristic(substr, length_substr, badchar);

    while (shift < length_str - length_substr) // текущий сдвиг < общее кол-во сдвигов
    {
        int32_t last_substr_char = length_substr - 1;

        while (last_substr_char >= 0 && substr[last_substr_char] == str[shift + last_substr_char])
        {
            last_substr_char--;
        }

        if (last_substr_char < 0) return str + shift;

        else
        {
            shift += find_max_between_two_num(1, last_substr_char - badchar[str[shift + last_substr_char]]);
        }
    }

    return NULL;
}