/**
 * @file abonent.h
 * @brief Основной функционал для работы со справочником.
 * @author amidalo
 */

#ifndef ABONENT_H
#define ABONENT_H

#include <stdlib.h>

/**
 * @brief Максимальное количество абонентов в справочнике.
 * 
 * @details Определяет емкость справочника.
 * Используется для статического выделения памяти под массив. 
 * 
 * @warning Операция добавления будет прерываться, если пытаться добавить больше положенного.
 */
#define MAX_NUMBER_OF_ABONENTS 100

/**
 * @brief Максимальное количество символов для имени абонента.
 * 
 * @details На самом деле, имя абонента содержит в себе 9 символов, 10 символ является null-terminator.
 * 
 * @warning При попытке ввести больше положенного, имя будет обрезаться.
 */
#define MAX_NAME_LENGTH 10

/**
 * @brief Максимальное количество символов для фамилии абонента.
 * 
 * @details На самом деле, фамилия абонента содержит в себе 9 символов, 10 символ является null-terminator.
 * 
 * @warning При попытке ввести больше положенного, фамилия будет обрезаться.
 */
#define MAX_SECOND_NAME_LENGTH 10

/**
 * @brief Максимальное количество символов для номера телефона абонента.
 * 
 * @details На самом деле, номер телефона абонента содержит в себе 9 символов, 10 символ является null-terminator.
 * 
 * @warning При попытке ввести больше положенного, номер телефона будет обрезаться.
 */
#define MAX_TEL_LENGTH 10

/**
 * @brief Структура, которая представляет собой абонента в справочнике.
 * 
 * @details Хранит в себе идентификатор, имя, фамилию, телефон абонента. 
 */
struct abonent
{
    int id;

    char name[MAX_NAME_LENGTH];
    char second_name[MAX_SECOND_NAME_LENGTH];
    char tel[MAX_TEL_LENGTH];
};

/**
 * @brief Узел для реализации двусвязного списка, хранит информацию об абоненте, ссылки на следующий и предыдущий узлы.
 */
struct node
{
    struct node* next;
    struct node* prev;

    struct abonent data;
};

/**
 * @brief Реализация абонентского справочника в виде двусвязного списка
 */
struct telephone_directory
{
    struct node* head;
    struct node* tail;
    
    int count_of_existing_records;
    int next_id;
};

/**
 * @brief Добавляет нового абонента в справочник.
 * 
 * @details Запрашивает данные нового абонента (имя, фамилия, телефон).
 * Сохраняет данные в предостваленную структуру.
 * После успешного добавления в справочник увеличивает счетчик существующих записей.
 * 
 * @param[out] abonent Указатель на структуру abonent для ее заполнения.
 * @param[in, out] count_of_existing_records Указатель на счетчик существующих записей.
 * 
 * @note Функция запрашивает ввод следующих полей:
 * 1. Имя (максимум 9 символов + null-terminator);
 * 2. Фамилия (максимум 9 символов + null-terminator);
 * 3. Номер телефона (максимум 9 цифр + null-terminator).
 * 
 * @warning Если справочник переполнен, то добавления абонента не произойдет.
 * 
 * @return Нет возвращаемого значения.
 */
void add_abonent(struct telephone_directory* tel_dir, const char* name,
                 const char* second_name, const char* tel);

/**
 * @brief Удаляет конкретного абонента из справочника по его индексу.
 * 
 * @details
 * 
 * @param[in, out]
 * @param[in, out]
 * 
 * @note
 * 
 * @return Нет возвращаемого значения.
 */
void delete_abonent_by_id(struct telephone_directory* tel_dir, int id);

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

void find_abonent_by_name(struct telephone_directory* tel_dir, const char* desired_name);

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
void print_all_abonents(struct telephone_directory* tel_dir);

#endif