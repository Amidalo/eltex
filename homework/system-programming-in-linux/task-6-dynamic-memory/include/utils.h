/**
 * @file utils.h
 * @brief Вспомогательные функции.
 * @author amidalo
 */

#ifndef UTILS_H
#define UTILS_H

#include <malloc.h>
#include "abonent.h"

/**
 * @brief Выводит меню управления справочником в консоль, в стандартный поток вывода (stdout).
 * 
 * @details Меню предлагает: добавить, удалить, поиск по имени, вывод всех записей, выход.
 * 
 * @note Отображает только меню, не обрабатывает выбор пользователя.
 * 
 * @return Нет возвращаемого значения.
 */
void print_text_menu(void);

/**
 * @brief Очищает стандартный поток ввода (stdin) от оставшихся символов.
 * 
 * @details Считывает и отбрасывает символы из stdin до символа '\n' или конца файла.
 * 
 * @note Использует inline для оптимизации.
 * 
 * @return Нет возвращаемого значения.
 */
void clean_stdin(void);

/**
 * @brief Обрабатывает строку, которую ввел пользователь во время назначения полей абонента.
 * 
 * @details Удаляет символ '\n' из конца строки, если он там есть, либо очищает stdin, если строка была обрезана.
 * 
 * @param[in, out] field Указатель на строку для ее обработки.
 * @param[in] field_size Максимальный размер строки/поля/буфера.
 * 
 * @see clean_stdin() для очистки буфера ввода.
 * 
 * @return Нет возвращаемого значения.
 */
void enter_field_with_validation(char* field, size_t field_size);

/**
 * 
 */
struct node* create_abonent_node(int id, const char* name, const char* second_name, const char* tel);

/**
 * 
 */
void free_all_abonents(struct telephone_directory* tel_dir);

#endif