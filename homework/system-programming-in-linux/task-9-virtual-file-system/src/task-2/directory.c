/**
 * @file    directory.c
 * @author  amidalo
 * @version 0.0.1
 * @date    26-Февраль-2026
 * @brief   Реализация функций для работы с директориями файлового менеджера.
 */

 /**
  * @brief Макрос _POSIX_C_SOURCE со значением 200809L включает функции: scandir, alphasort.
  */
#define _POSIX_C_SOURCE 200809L

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "directory.h"

/**
 * @brief   Читает содержимое директории и заполняет массив файлов панели.
 * 
 * @details Использует scandir для получения отсортированного списка файлов.
 *          Для каждого файла (кроме ".") получает информацию через stat и
 *          заполняет структуру file. Результат сохраняется в panel->files.
 * 
 * @param   panel [in] Указатель на панель, в которую загружаются файлы.
 * @param   path  [in] Путь к директории для чтения.
 * 
 * @return  void.
 * 
 * @note    При ошибках panel == NULL, path == NULL программа завершается аварийно.
 * @note    При ошибке scandir < 0 функция завершается досрочно.
 * @note    Файлы сортируются в алфавитном порядке благодаря alphasort.
 * @note    Максимальное количество файлов ограничено MAX_FILES.
 */
void read_directory(struct panel* panel, const char* path)
{
    if (panel == NULL)
    {
        printf("\n Ошибка: при чтении директории указатель на 'panel' NULL! \n");
        exit(EXIT_FAILURE);
    }

    if (path == NULL)
    {
        printf("\n Ошибка: при чтении директории указатель на 'path' NULL! \n");
        exit(EXIT_FAILURE);
    }

    struct dirent **namelist;
    struct stat st;
    char full_path[PATH_MAX];
    int count_found_records_in_dir;
    
    panel->file_count = 0;
    
    count_found_records_in_dir = scandir(path, &namelist, NULL, alphasort);
    if (count_found_records_in_dir < 0) return;
    
    for (int i = 0; i < count_found_records_in_dir && panel->file_count < MAX_FILES; i++) 
    {
        if (strcmp(namelist[i]->d_name, ".") == 0) 
        {
            free(namelist[i]);
            continue;
        }
        
        snprintf(full_path, sizeof(full_path), "%s/%s", path, namelist[i]->d_name);
        
        if (stat(full_path, &st) == 0) {
            strcpy(panel->files[panel->file_count].name, namelist[i]->d_name);
            strcpy(panel->files[panel->file_count].path, full_path);
            panel->files[panel->file_count].is_dir = S_ISDIR(st.st_mode);
            panel->files[panel->file_count].size = st.st_size;
            panel->file_count++;
        }
        
        free(namelist[i]);
    }
    free(namelist);
}

/**
 * @brief   Изменяет текущую директорию панели.
 * 
 * @details Обрабатывает два случая:
 *          1) переход ".." - поднятие на уровень вверх.
 *          2) переход в поддиректорию - добавление имени к текущему пути.
 *          После изменения пути перечитывает содержимое новой директории
 *          и сбрасывает индексы выбора и прокрутки.
 * 
 * @param   panel [in] указатель на панель
 * @param   path  [in] путь для перехода (".." или имя поддиректории)
 * 
 * @return  void
 * 
 * @note    Если panel == NULL или path == NULL, программа завершается аварийно.
 * @note    После успешного перехода вызывается read_directory().
 * @note    Индексы выбора и прокрутки сбрасываются в 0.
 */
void change_directory(struct panel* panel, const char* path)
{
    if (panel == NULL)
    {
        printf("\n Ошибка: при смене директории указатель на 'panel' NULL! \n");
        exit(EXIT_FAILURE);
    }

    if (path == NULL)
    {
        printf("\n Ошибка: при смене директории указатель на 'path' NULL! \n");
        exit(EXIT_FAILURE);
    }

    char new_path[PATH_MAX];
    
    if (strcmp(path, "..") == 0) 
    {
        char *last_slash = strrchr(panel->current_path, '/');
        if (last_slash != NULL && last_slash != panel->current_path) 
        {
            *last_slash = '\0';
        } 
        else if (strcmp(panel->current_path, "/") != 0) 
        {
            strcpy(panel->current_path, "/");
        }
    }
    else 
    {
        strncpy(new_path, panel->current_path, sizeof(new_path) - 1);
        new_path[sizeof(new_path) - 1] = '\0';
        
        size_t len = strlen(new_path);
        if (len > 0 && new_path[len - 1] != '/' && len < sizeof(new_path) - 2) {
            strncat(new_path, "/", sizeof(new_path) - len - 1);
            len++;
        }
        
        if (len < sizeof(new_path) - 1) {
            strncat(new_path, path, sizeof(new_path) - len - 1);
        }
        
        strcpy(panel->current_path, new_path);
    }
    
    read_directory(panel, panel->current_path);
    panel->selected_file_saved_index = 0;
    panel->first_visible_file_index = 0;
}