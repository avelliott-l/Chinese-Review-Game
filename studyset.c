#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "studyset.h"
#include "gui.h"

// add manually or import file
void new_study_set() {

    /* change settings so user can see what they enter */
    echo();  
    nocbreak();
    char file_name[50];

    printw("%s%s", "NOTE: All files must be .txt and formatted such that each ",
     "vocab term is on it\'s own line in the format:\n\"English | 汉子\"\n");
    printw("Enter the filename in the box below.\n");
    refresh();

    /* create input box */
    int y, x;
    getyx(stdscr, y, x);
    WINDOW *enter_name = newwin(3, 60, y, x);
    box(enter_name, 0, 0);

    mvwprintw(enter_name, 1, 2, ""); // move cursor into the box
    wgetstr(enter_name,file_name);
    noecho();
    cbreak();
    delwin(enter_name);
    clear();

    FILE *study_set;
    sprintf(file_name, "%s.txt", file_name);

    // clear if file exists

    /* file does not exists */
    study_set = fopen(file_name, "r");
    if (study_set == NULL) {
        printw("File does not exist\n");
        printw("Would you like to try again?\n");

        int choice = 0;
        keypad(stdscr, TRUE);
        print_yn_menu(stdscr, 1, &choice);
        keypad(stdscr, FALSE);
        clear();

        if (choice == 1) {
            new_study_set();
        } else if (choice == 2) {
            print_menu(TRUE, 3);
            return;
        }
    }

    fclose(study_set);
    printw("Study set added!\n\n");
    printw("Press any charcter to return to the main menu.\n");
    getch();
    clear();
    print_menu(FALSE, 0);

}