/**
 * @file main.c
 * @author amidalo
 * @version 0.0.1
 * @date 26-Февраль-2026
 * @brief 
 */

#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "file_manager.h"
#include "ui.h"
#include "directory.h"

void sig_winch(int signal)
{
    (void)signal;
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);
    resizeterm(size.ws_row, size.ws_col);
}

int main(void)
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    
    struct panel* left_panel = create_panel(cwd);
    struct panel* right_panel = create_panel(cwd);
    int* active_panel = create_active_panel();
    
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    
    signal(SIGWINCH, sig_winch);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    refresh();
    
    read_directory(left_panel, cwd);
    read_directory(right_panel, cwd);
    
    redraw_windows(left_panel, right_panel, *active_panel);
    
    int ch;
    while (1) {
        ch = getch();
        handle_input(ch, left_panel, right_panel, active_panel);
        redraw_windows(left_panel, right_panel, *active_panel);
    }
    
    endwin();
    destroy_panel(left_panel);
    destroy_panel(right_panel);
    destroy_active_panel(active_panel);
    exit(EXIT_SUCCESS);
}