#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <locale.h>
#include "gui.h"

int main() {

    /* include support for chinese characters */
    setlocale(LC_ALL, "");

    /* start NCURSES */
    initscr();
    clear();
    noecho();
    cbreak();

    bool continue_execution = FALSE;
    start_program(&continue_execution);

    
    if (continue_execution == TRUE) {
        print_menu(FALSE, 0);
    }
    
    endwin();
    
}