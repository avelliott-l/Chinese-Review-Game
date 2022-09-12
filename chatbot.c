#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <locale.h>
#include "gui.h"


/* function choices for main menu */
char *menu_choices[] = {
    "Review",
    "Quiz me!",
    "Add a new study set",
    "View a study set",
    "Delete a study set",
    "Exit"
};
int n_choices = sizeof(menu_choices) / sizeof(char*);


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

    printw("here1");
        refresh();
    
    if (continue_execution == TRUE) {

        printw("here2");
        refresh();

        /* create main menu */
        int height = 20, width = 20;
        int startx = (COLS - width) / 2;
        int starty = (LINES - height) / 2;
        int highlight = 1;
        int choice = 0;  // keep track of which menu option is chosen
        WINDOW *menu_win = newwin(height, width, starty, startx);
        print_menu(menu_win, highlight, menu_choices, n_choices);
        refresh();
        wrefresh(menu_win);
        keypad(menu_win, TRUE);

        printw("here3");
        refresh();

        

        printw("here4");
        refresh();

        while(1) {

            int c = wgetch(menu_win);
            switch (c) {
                case KEY_UP:
                    if (highlight == 1) {
                        highlight = n_choices;
                    } else {
                        highlight--;
                    }
                    break;
                case KEY_DOWN:
                    if (highlight == n_choices) {
                        highlight = 1;
                    } else {
                        highlight++;
                    }
                    break;
                case 10:
                    choice = highlight;
                    break;
                default:
                    // ADD CONTROLS!!
                    break;
            }

            print_menu(menu_win, highlight, menu_choices, n_choices);
            
            if (choice != 0) {
                break;
            }
        }
    }

    printw("here5");
        refresh();
    
    endwin();
    
}

