/**
 * @file abonent.c
 * @brief Реализация основного функционала справочника.
 * @author amidalo
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "abonent.h"
#include "utils.h"

/**
 * @brief Добавляет нового абонента в справочник, запрашивая данные у пользователя.
 * 
 * @details Алгоритм:
 * 1) Проверка указателей на NULL;
 * 2) Для каждого поля происходит чтение из stdin через fgets();
 * 3) Каждое поле обрабатывается через функцию check_field_input();
 * 4) Инкремент счетчика записей.
 * 
 * @param[out] abonent Указатель на структуру abonent для ее заполнения.
 * @param[in, out] count_of_existing_records Указатель на счетчик существующих записей.
 * 
 * @return Нет возвращаемого значения.
 */
void add_abonent(struct abonent* abonent, int8_t* count_of_existing_records)
{
    if (abonent == NULL)
    {
        printf("\n Ошибка: указатель на структуру NULL! \n");
        return;
    }

    if (count_of_existing_records == NULL)
    {
        printf("\n Ошибка: указатель на счетчик NULL! \n");
        return;
    }

    printf("\n Введите имя: "); 
    fgets(abonent->name, MAX_NAME_LENGTH, stdin);
    check_field_input(abonent->name);

    printf("\n Введите фамилию: ");
    fgets(abonent->second_name, MAX_SECOND_NAME_LENGTH, stdin);
    check_field_input(abonent->second_name);

    printf("\n Введите номер телефона: ");
    fgets(abonent->tel, MAX_TEL_LENGTH, stdin);
    check_field_input(abonent->tel);

    (*count_of_existing_records)++;
}

/**
 * @brief
 * 
 * @details
 * 
 * @param
 * 
 * @note
 * 
 * @return Нет возвращаемого значения.
 */
void delete_abonent_by_index(struct abonent* abonents, int8_t* count_of_existing_records, int8_t one_based_index)
{
    if (abonents == NULL || count_of_existing_records == NULL)
    {
        printf("\n Ошибка: указатель на массив структур и/или на количество записей равен NULL! \n");
        return;
    }

    int8_t zero_based_index = one_based_index - 1;
    
    if (zero_based_index < 0 || zero_based_index >= *count_of_existing_records)
    {
        printf("\n Недопустимый индекс! Допустимый индекс должен быть в диапазоне 1 - %d \n", *count_of_existing_records);
        return;
    }
    
    for (int i = zero_based_index; i < *count_of_existing_records - 1; i++)
    {
        abonents[i] = abonents[i + 1];
    }

    memset(&abonents[*count_of_existing_records - 1], 0, sizeof(struct abonent));
    (*count_of_existing_records)--;

    printf("\n Абонент удален! \n");
}

/**
 * @brief
 * 
 * @details
 * 
 * @param
 * 
 * @note
 * 
 * @return Нет возвращаемого значения.
 */
void find_all_abonents_by_name(struct abonent* abonents, int8_t* count_of_existing_records, char* desired_name)
{
    if (abonents == NULL)
    {
        printf("\n Ошибка: указатель на массив структур NULL! \n");
        return;
    }

    if (desired_name == NULL)
    {
        printf("\n Ошибка: указатель на строку NULL! \n");
        return;
    }
    
    for (int32_t i = 0; i < *count_of_existing_records; i++)
    {
        if (strcmp(abonents[i].name, desired_name) == 0)
        {
            printf("%d) Имя: %s; Фамилия: %s; Телефон: %s\n",
                i + 1, abonents[i].name, abonents[i].second_name, abonents[i].tel);
        }
        
    }
    
}

/**
 * @brief
 * 
 * @details
 * 
 * @param
 * 
 * @note
 * 
 * @return Нет возвращаемого значения.
 */
void print_all_abonents(struct abonent* abonents, int8_t* count_of_existing_records)
{
    if (abonents == NULL)
    {
        printf("\n Ошибка: указатель на массив структур NULL! \n");
        return;
    }

    if (*count_of_existing_records < 1)
    {
        printf("\n Нет ни одной записи. Список абонентов пуст! \n");
        return;
    }

    printf("\n Вывод всех %d абонентов: \n", *count_of_existing_records);

    for (int32_t i = 0; i < *count_of_existing_records; i++)
    {
        printf("%d) Имя: %s; Фамилия: %s; Телефон: %s\n",
            i + 1, abonents[i].name, abonents[i].second_name, abonents[i].tel);
    }
}