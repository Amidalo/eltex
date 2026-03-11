/**
 * @file    ui.c
 * @author  amidalo
 * @version 0.0.1
 * @date    26-Февраль-2026
 * @brief   Реализация функций пользовательского интерфейса файлового менеджера.
 */

#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ui.h"
#include "directory.h"

/**
 * @brief   Отрисовывает одну панель файлового менеджера.
 * 
 * @details Функция отображает панель с рамкой, заголовком (текущий путь)
 *          и списком файлов с учётом прокрутки. Для директорий используется
 *          жирный шрифт и цветовая пара 1, для файлов отображается размер.
 *          Активная панель выделяется жирной рамкой, а выбранный файл
 *          подсвечивается инверсией.
 * 
 * @param   panel     [in] Указатель на отрисовываемую панель.
 * @param   width     [in] Ширина панели в символах.
 * @param   height    [in] Высота панели в символах.
 * @param   is_active [in] Флаг активности (1 - панель активна, 0 - неактивна).
 * 
 * @return  void.
 * 
 * @note    Панель должна иметь инициализированное окно (panel->win).
 * @note    Цветовая пара 1 инициализирована в main().
 * @note    Формат вывода: /имя_директории для папок, имя_файла размер для файлов.
 */
void draw_panel(struct panel* panel, int width, int height, int is_active)
{
    if (!panel || !panel->win) return;
    
    WINDOW* win = panel->win;
    int max_items = height - 2;
    
    werase(win);
    
    if (is_active) {
        wattron(win, A_BOLD);
        box(win, '|', '-');
        wattroff(win, A_BOLD);
    } else {
        box(win, '|', '-');
    }
    
    wattron(win, A_REVERSE);
    mvwprintw(win, 0, 2, " %s ", panel->current_path);
    wattroff(win, A_REVERSE);
    
    for (int i = 0; i < max_items && (i + panel->first_visible_file_index) < panel->file_count; i++) {
        int file_idx = i + panel->first_visible_file_index;
        struct file* file = &panel->files[file_idx];
        
        if (file_idx == panel->selected_file_saved_index && is_active) {
            wattron(win, A_REVERSE);
        }
        
        if (file->is_dir) {
            wattron(win, A_BOLD | COLOR_PAIR(1));
            mvwprintw(win, i + 1, 1, "/%-*s", width - 3, file->name);
            wattroff(win, A_BOLD | COLOR_PAIR(1));
        } else {
            char size_str[16];
            if (file->size < 1024)
                snprintf(size_str, sizeof(size_str), "%ld B", file->size);
            else if (file->size < 1024 * 1024)
                snprintf(size_str, sizeof(size_str), "%.1f KB", file->size / 1024.0);
            else
                snprintf(size_str, sizeof(size_str), "%.1f MB", file->size / (1024.0 * 1024.0));
            
            mvwprintw(win, i + 1, 1, " %-*s %10s", width - 15, file->name, size_str);
        }
        
        if (file_idx == panel->selected_file_saved_index && is_active) {
            wattroff(win, A_REVERSE);
        }
    }
    
    wrefresh(win);
}

/**
 * @brief   Перерисовывает обе панели файлового менеджера.
 * 
 * @details Функция вызывается при изменении размера терминала (SIGWINCH)
 *          или после обновления содержимого панелей. Удаляет старые окна
 *          и создаёт новые с актуальными размерами, затем отрисовывает
 *          обе панели с учётом активной.
 * 
 * @param   left_panel   [in] Указатель на левую панель.
 * @param   right_panel  [in] Указатель на правую панель.
 * @param   active_panel [in] Номер активной панели (0 - левая, 1 - правая).
 * 
 * @return  void.
 * 
 * @note    Использует глобальные переменные LINES и COLS из ncurses.
 * @note    Каждая панель занимает ровно половину ширины терминала.
 * @note    После создания окон вызывает draw_panel() для каждой панели.
 */
void redraw_windows(struct panel* left_panel, struct panel* right_panel, int active_panel)
{
    int height = LINES;
    int width = COLS / 2;
    
    if (left_panel->win != NULL)
        delwin(left_panel->win);
    if (right_panel->win != NULL)
        delwin(right_panel->win);
    
    left_panel->win = newwin(height, width, 0, 0);
    right_panel->win = newwin(height, width, 0, width);
    
    draw_panel(left_panel, width, height, active_panel == 0);
    draw_panel(right_panel, width, height, active_panel == 1);
    
    refresh();
}

/**
 * @brief   Обрабатывает пользовательский ввод.
 * 
 * @details Функция определяет активную панель и выполняет действия:
 *          - Tab: переключение между левой и правой панелью.
 *          - Стрелка вверх: перемещение выделения вверх.
 *          - Стрелка вниз: перемещение выделения вниз.
 *          - Enter: вход в выбранную директорию.
 *          - q/Q: выход из программы.
 * 
 * @param   ch           [in] Код нажатой клавиши (из getch()).
 * @param   left_panel   [in] Указатель на левую панель.
 * @param   right_panel  [in] Указатель на правую панель.
 * @param   active_panel [in/out] Указатель на переменную номера активной панели.
 * 
 * @return  void.
 */
void handle_input(int ch, struct panel* left_panel, struct panel* right_panel, int* active_panel)
{
    struct panel* active = (*active_panel == 0) ? left_panel : right_panel;
    
    switch(ch) {
        case '\t':
            *active_panel = !(*active_panel);
            break;
            
        case KEY_UP:
            if (active->selected_file_saved_index > 0) 
            {
                active->selected_file_saved_index--;
                if (active->selected_file_saved_index < active->first_visible_file_index)
                    active->first_visible_file_index = active->selected_file_saved_index;
            }
            break;
            
        case KEY_DOWN:
            if (active->selected_file_saved_index < active->file_count - 1) 
            {
                active->selected_file_saved_index++;
                if (active->selected_file_saved_index >= active->first_visible_file_index + LINES - 2)
                    active->first_visible_file_index = active->selected_file_saved_index - (LINES - 3);
            }
            break;
            
        case KEY_ENTER:
        case 10:
            if (active->file_count > 0 && active->files[active->selected_file_saved_index].is_dir) 
            {
                change_directory(active, active->files[active->selected_file_saved_index].name);
            }
            break;
            
        case 'q':
        case 'Q':
            endwin();
            exit(EXIT_SUCCESS);
            break;
    }
}