/**
 * @file    file_manager.c
 * @author  amidalo
 * @version 0.0.1
 * @date    26-Февраль-2026
 * @brief   Реализация функций для создания и управления панелями файлового менеджера.
 */

#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "file_manager.h"

/**
 * @brief   Создает новую панель файлового менеджера.
 * 
 * @details Выделяет память под структуру panel, инициализирует все поля
 *          начальными значениями и копирует указанный путь в current_path.
 *          В случае ошибки выделения памяти или NULL пути программа завершается.
 * 
 * @param   path [in] Путь к директории для инициализации панели (не должен быть NULL).
 * 
 * @return  struct panel* Указатель на созданную структуру panel.
 * 
 * @note    При ошибке выделения памяти или NULL пути вызывает exit(EXIT_FAILURE).
 * 
 * @warning path не должен быть NULL, иначе программа аварийно завершится.
 */
struct panel* create_panel(const char* path)
{
    if (path == NULL)
    {
        printf("\n Ошибка: при создании панели указатель на 'path' NULL! \n");
        exit(EXIT_FAILURE);
    }

    struct panel* panel = (struct panel*)malloc(sizeof(struct panel));
    if (panel == NULL)
    {
        printf("\n Ошибка: при создании панели указатель на структуру 'panel' NULL! \n");
        exit(EXIT_FAILURE);
    }

    panel->win = NULL;
    panel->file_count = 0;
    panel->selected_file_saved_index = 0;
    panel->first_visible_file_index = 0;

    strncpy(panel->current_path, path, PATH_MAX - 1);
    panel->current_path[PATH_MAX - 1] = '\0';

    return panel;
}

/**
 * @brief   Уничтожает панель и освобождает занимаемую память.
 * 
 * @details Удаляет окно ncurses (если оно было создано) и освобождает
 *          память, выделенную под структуру panel. При обнаружении NULL указателей
 *          программа завершается с сообщением об ошибке.
 * 
 * @param   panel [in] Указатель на уничтожаемую панель.
 * 
 * @return  void.
 * 
 * @note    При обнаружении NULL указателей вызывает exit(EXIT_FAILURE).
 * 
 * @warning panel не должен быть NULL, panel->win не должен быть NULL,
 *          иначе программа аварийно завершится.
 */
void destroy_panel(struct panel* panel)
{
    if (panel == NULL) 
    {
        printf("\n Ошибка: при удалении панели указатель на структуру 'panel' NULL! \n");
        exit(EXIT_FAILURE);
    }

    if (panel->win == NULL) 
    {
        printf("\n Ошибка: при удалении панели указатель на поле 'win' структуры 'panel' NULL! \n");
        exit(EXIT_FAILURE);
    }

    delwin(panel->win);
    free(panel);
}

/**
 * @brief   Создает указатель на переменную, которая хранит номер активной панели.
 * 
 * @details Выделяет память под переменную типа int и устанавливает её значение в 0,
 * что соответствует активной левой панели. В случае ошибки выделения памяти
 * программа завершается.
 * 
 * @note    0 - левая панель активна, 1 - правая панель активна.
 * 
 * @param   void.
 * 
 * @return  int* Указатель на переменную с номером активной панели.
 * 
 * @warning При ошибке выделения памяти вызывает exit(EXIT_FAILURE).
 */
int* create_active_panel(void)
{
    int* active = (int*)malloc(sizeof(int));
    if (active == NULL) 
    {
        printf("\n Ошибка: указатель на переменную 'active' NULL! \n");
        exit(EXIT_FAILURE);
    }

    *active = 0;

    return active;
}

/**
 * @brief   Уничтожает указатель на переменную активной панели.
 * 
 * @details Освобождает память, выделенную под переменную, хранящую номер
 *          активной панели. При обнаружении NULL указателя программа завершается.
 * 
 * @param   active_panel [in] Указатель на переменную активной панели.
 * 
 * @return  void.
 * 
 * @note    При обнаружении NULL указателя вызывает exit(EXIT_FAILURE).
 * 
 * @warning active_panel не должен быть NULL, иначе программа аварийно завершится.
 */
void destroy_active_panel(int* active_panel)
{
    if (active_panel == NULL)
    {
        printf("\n Ошибка: не удалось высвободить память!" 
               " Указатель на 'active_panel' NULL! \n");
        exit(EXIT_FAILURE);
    }
    
    free(active_panel);
}