/**
 * @file    file_manager.h
 * @author  amidalo
 * @version 0.0.1
 * @date    26-Февраль-2026
 * @brief   Заголовочный файл с определениями структур и функций файлового менеджера.
 */

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <sys/types.h>
#include <curses.h>

/**
 * @brief Максимальное количество файлов в панели.
 */
#define MAX_FILES 1000

/**
 * @brief Максимальная длина пути.
 */
#define PATH_MAX 4096

/**
 * @struct file
 * @brief Структура, представляющая файл или директорию.
 */
struct file
{
    char name[256];
    char path[PATH_MAX];
    int is_dir;
    off_t size;
};

/**
 * @struct panel
 * @brief Структура, представляющая панель файлового менеджера.
 */
struct panel
{
    WINDOW* win;
    struct file files[MAX_FILES];
    int file_count;
    int selected_file_saved_index;
    int first_visible_file_index;
    char current_path[PATH_MAX];
};

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
struct panel* create_panel(const char* path);

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
void destroy_panel(struct panel* panel);

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
int* create_active_panel(void);

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
void destroy_active_panel(int* active_panel);

#endif