/**
 * @file utils.c
 * @brief Реализация вспомогательных функций.
 * @author amidalo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "abonent.h"


/**
 * @brief Выводит текстовое меню телефонного справочника.
 * 
 * @details Использует один вызов функции printf() c конкатенацией строк.
 * Каждая строка начинается с символа '\n' для отступов.
 * 
 * @note Реализована как inline, так как сама по себе функция маленькая и часто вызывается.
 * 
 * @return Нет возвращаемого значения.
 */
inline void print_text_menu(void)
{
    printf("\n 1) Добавить абонента;"
           "\n 2) Удалить абонента;"
           "\n 3) Поиск абонентов по имени;"
           "\n 4) Вывод всех записей;"
           "\n 5) Выход. \n"
           "\n Ваш выбор: ");
}

/**
 * @brief Очищает буфер стандартного ввода от оставшихся в нем символов.
 * 
 * @details Алгоритм:
 * 1) Считывает по символу из stdin;
 * 2) Продолжает до тех пор, пока не встретиться символ '\n' или конец строки;
 * 3) Никуда не сохраняет считанные символы. 
 * 
 * @note Реализована как inline, так как часто вызывается в программе.
 * 
 * @return Нет возвращаемого значения.
 */
inline void clean_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
}

/**
 * @brief Обрабатывает строку после fgets(), а именно удаляет '\n' или очищает stdin.
 * 
 * @details Алгоритм:
 * 1) Если строка содержит '\n' в конце, то заменяет его на '\0'.
 * 2) Если строка не содержит '\n', то вызывает функцию clean_stdin() для очистки stdin от остатков.
 * 
 * @param[in, out] field Указатель на строку для ее обработки.
 * @param[in] field_size Максимальный размер строки/поля/буфера.
 * 
 * @return Нет возвращаемого значения.
 */
void enter_field_with_validation(char* field, size_t field_size)
{
    if (field == NULL)
    {
        printf("\n Ошибка: указатель на поле NULL! \n");
        return;
    }

    if (field_size == 0)
    {
        printf("\n Ошибка: нулевой размер буфера! \n");
        return;
    }
    
    fgets(field, field_size, stdin);
    
    size_t length = 0;

    length = strlen(field);

    if (length > 0 && field[length - 1] == '\n')
    {
        field[length - 1] = '\0';
    }
    else if (length == field_size - 1)
    {
        clean_stdin();
    }
}

/**
 * @brief Создает узел с информацией об абоненте, его имя, фамилия, телефон.
 * 
 * @details Алгоритм:
 * 1) Создаем указатель на структуру, указывающий на область памяти, где эта структура будет храниться.
 * 2) Проверяем, что память выделилась успешно. Если нет, то немедленно завершаем программу.
 * 3) Копируем с помощью strncpy переданный параметр функции в поле переданной функции.
 * 4) prev, next = NULL, так как мы еще не знаем про существование других узлов в данном случае.
 * 
 * @note Если память не была выделена успешно, программа завершится аварийно.
 * 
 * @param[in] id Идентификатор абонента.
 * @param[in] name Указатель на имя абонента.
 * @param[in] second_name Указатель на фамилию абонента.
 * @param[in] tel Указатель на номер телефона абонента.
 * 
 * @return Возвращает указатель на структуру узла.
 */
struct node* create_abonent_node(int id, const char* name, const char* second_name, const char* tel)
{
    struct node* node = (struct node*) malloc(sizeof(struct node));
    
    if (node == NULL)
    {
        perror("\n Ошибка: указатель на выделенную структуру 'node' NULL! \n");
        exit(EXIT_FAILURE);
    }

    node->data.id = id;

    strncpy(node->data.name, name, sizeof(node->data.name) - 1);
    node->data.name[sizeof(node->data.name) - 1] = '\0';

    strncpy(node->data.second_name, second_name, sizeof(node->data.second_name) - 1);
    node->data.second_name[sizeof(node->data.second_name) - 1] = '\0';

    strncpy(node->data.tel, tel, sizeof(node->data.tel) - 1);
    node->data.tel[sizeof(node->data.tel) - 1] = '\0';

    node->next = NULL;
    node->prev = NULL;

    return node;
}

/**
 * 
 */
void free_all_abonents(struct telephone_directory* tel_dir)
{
    if (tel_dir == NULL)
    {
        printf("\n Ошибка: указатель на выделенную структуру 'node' NULL! \n");
        exit(EXIT_FAILURE);
    }
    
    struct node* current_node = tel_dir->head;
    while (current_node != NULL)
    {
        struct node* next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    tel_dir->head = NULL;
    tel_dir->tail = NULL;
}