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
 * @brief Добавляет нового абонента в справочник.
 * 
 * @details Алгоритм:
 * 1) Проверка указателей на NULL.
 * 2) Создание абонентского узла.
 * 3) Если справочник пуст, созданный узел будет являться головой и хвостом.
 * 4) Иначе меняем указатель next текущего хвоста на созданный узел,
 * указатель prev созданного узла указываем на текущий хвост,
 * обновляем хвост.
 * 
 * @param[in, out] tel_dir Указатель на справочник.
 * @param[in] name Указатель на имя абонента.
 * @param[in] second_name Указатель на фамилию абонента.
 * @param[in] tel Указатель на поле номер телефона абонента.
 * 
 * @return Нет возвращаемого значения.
 */
void add_abonent(struct telephone_directory* tel_dir, const char* name,
                 const char* second_name, const char* tel)
{
    if (tel_dir == NULL)
    {
        printf("\n Ошибка: указатель на структуру 'tel_dir' NULL! \n");
        exit(EXIT_FAILURE);
    }

    struct node* node = create_abonent_node(tel_dir->next_id, name, second_name, tel);

    if (node == NULL)
    {
        printf("\n Ошибка: указатель на структуру 'node' NULL! \n");
        exit(EXIT_FAILURE);
    }

    tel_dir->next_id++;

    if (tel_dir->head == NULL) // Если справочник пуст
    {
        tel_dir->head = node;
        tel_dir->tail = node;
    } else {
        tel_dir->tail->next = node; // теперь указатель next текущего хвоста указывает на новый узел
        node->prev = tel_dir->tail; // указатель prev нового узла указывает текущий хвост
        tel_dir->tail = node;       // обновляем хвост
    }

    tel_dir->count_of_existing_records++;
    printf("\n Абонент добавлен! \n");
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
void delete_abonent_by_id(struct telephone_directory* tel_dir, int id)
{
    if (tel_dir == NULL)
    {
        printf("\n Ошибка: указатель на структуру 'tel_dir' NULL! \n");
        exit(EXIT_FAILURE);
    }

    struct node* current_node = tel_dir->head;

    while (current_node != NULL)
    {
        if (current_node->data.id == id) // Если id совпадают
        {
            if (current_node == tel_dir->head) // Если это голова
            {
                tel_dir->head = current_node->next; // Головой становится следующая нода
                if (tel_dir->head != NULL) // Если голова не указывает на NULL
                {
                    tel_dir->head->prev = NULL;
                }
            }
            else if (current_node == tel_dir->tail) // Если это хвост
            {
                tel_dir->tail = current_node->prev;
                if (tel_dir->tail != NULL)
                {
                    tel_dir->tail->next = NULL;
                }
            }
            else
            {
                current_node->prev->next = current_node->next;
                current_node->next->prev = current_node->prev;
            }
            
            free(current_node);
            tel_dir->count_of_existing_records--;

            printf("\n Абонент удален! \n");

            if (tel_dir->head == NULL)
            {
                tel_dir->tail == NULL;
            }
            
            return;
        }
        current_node = current_node->next;
    }
    printf("\n Абонент не найден. \n");
}

/**
 * @brief Находит первое вхождение строки, которую ввел пользователь для поиска
 * имени. Выводит всех абонентов, если введенная строка вошла в имя абонента.
 * 
 * @details Алгоритм:
 * 1) Проверка указателя tel_dir на NULL, desired_name на NULL и > 0. 
 * 2) Создаем указатель на голову/начало справочника.
 * 3) Проходим по справочнику до тех пор, пока не встретим NULL.
 * 4) Если есть вхождение, то выводим в стандартный поток вывода.
 * 
 * @param[in] tel_dir Указатель на справочник.
 * @param[in] desired_name Указатель на желаемое имя.
 * 
 * @note Используется char *strstr(const char *haystack, const char *needle);
 * 
 * 
 * @return Нет возвращаемого значения.
 */
void find_abonent_by_name(struct telephone_directory* tel_dir, const char* desired_name)
{
    if (tel_dir == NULL)
    {
        printf("\n Ошибка: указатель на структуру 'tel_dir' NULL! \n");
        exit(EXIT_FAILURE);
    }

    if (desired_name == NULL)
    {
        printf("\n Ошибка: указатель на строку 'desired_name' NULL! \n");
        exit(EXIT_FAILURE);
    }

    if (strlen(desired_name) == 0)
    {
        printf("\n Ошибка: длина искомого имени не может быть равна 0! \n");
        return;
    }
    
    struct node* current_node = tel_dir->head;
    
    while (current_node != NULL)
    {
        if (strstr(current_node->data.name, desired_name) != NULL)
        {
            printf("%d) Имя: %s; Фамилия: %s; Телефон: %s\n",
                current_node->data.id,
                current_node->data.name,
                current_node->data.second_name,
                current_node->data.tel);
        }
        current_node = current_node->next;
    }
    return;
}

/**
 * @brief Выводит в стандартный поток вывода список всех абонентов.
 * 
 * @details Алгоритм:
 * 1) Проверка указателя tel_dir на NULL.
 * 2) Создаем указатель на голову/начало справочника.
 * 3) Проходим по справочнику до тех пор, пока не встретим NULL.
 * 
 * @param[in] tel_dir Указатель на справочник.
 * 
 * @return Нет возвращаемого значения.
 */
void print_all_abonents(struct telephone_directory* tel_dir)
{
    if (tel_dir == NULL)
    {
        printf("\n Ошибка: указатель на структуру 'tel_dir' NULL! \n");
        exit(EXIT_FAILURE);
    }

    struct node* current_node = tel_dir->head;
    
    printf("\n Вывод всех %d абонентов: \n", tel_dir->count_of_existing_records);

    while (current_node != NULL)
    {
        printf("%d) Имя: %s; Фамилия: %s; Телефон: %s\n",
                current_node->data.id,
                current_node->data.name,
                current_node->data.second_name,
                current_node->data.tel);
        
        current_node = current_node->next;
    }
    return;
}