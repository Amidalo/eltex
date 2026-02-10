/**
 * @file abonent.h
 * @brief Основной функционал для работы со справочником.
 * @author amidalo
 */

#ifndef ABONENT_H
#define ABONENT_H

#include <stdint.h>

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
 * @details Хранит в себе имя, фамилию, телефон абонента. 
 */
struct abonent
{
    int8_t name[MAX_NAME_LENGTH];
    int8_t second_name[MAX_SECOND_NAME_LENGTH];
    int8_t tel[MAX_TEL_LENGTH];
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
void add_abonent(struct abonent* abonent, int8_t* count_of_existing_records);

/**
 * @brief Удаляет конкретного абонента из справочника по его индексу.
 * 
 * @details Запрашивает у пользователя индекс абонента, которого он хочет удалить из справочника.
 * Если был введен недопустимый индекс, то программа предупреждает пользователя об этом.
 * После удаления абонента, последующие абоненты смещаются назад, а счетчик уменьшается.
 * 
 * @param[in, out] abonents Указатель на массив структур.
 * @param[in, out] count_of_existing_records Указатель на число существующих записей в справочнике.
 * @param[in] one_based_index Индекс абонента, которого нужно удалить из справочника. 
 * Переменная называется так из-за того, что справочник начинается с числа 1, а не с 0.
 * Позже переменная преобразовывается в zero_based_index для удобства.
 * 
 * @note
 * 
 * @return Нет возвращаемого значения.
 */
void delete_abonent_by_index(struct abonent* abonents, int8_t* count_of_existing_records, int8_t one_based_index);

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
void find_all_abonents_by_name(struct abonent* abonents, int8_t* count_of_existing_records, char* desired_name);

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
void print_all_abonents(struct abonent* abonents, int8_t* count_of_existing_records);

#endif