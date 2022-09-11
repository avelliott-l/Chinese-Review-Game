#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdbool.h>
#include "gui.h"


/*
* print_menu: prints the menu window onto the terminal
*
* menu_win: pointer to the window terminal
* highlight: a an integer to indicate which choice is selected
*
*/
void print_menu(WINDOW *menu_win, int highlight, char **menu_choices, int n_choices) {

    int x = 2, y = 2;  // start coord values of 1st choice in menu
    box(menu_win, 0, 0);

    for (int i = 0; i < n_choices; i++) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", menu_choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", menu_choices[i]);
        }
        y++;
    }

    wrefresh(menu_win);
    
}

/*
* print_by_char: prints a string out character by character to roughly 
*                imitate typing
*
* win: the window the text will be printed onto
* string: the text to be printed out
*
*/
void print_by_char(WINDOW *win, char *string) {
    int len = strlen(string);
    for (int i = 0; i < len; i++){
        wprintw(win, "%c", string[i]);
        delay_output(100);
        refresh();
    }
}

void print_yn_menu(WINDOW *win, int highlight, char **choices){
    for (int i = 0; i < 2; i++) {
        int x, y;
        getyx(win, y, x);
        if (highlight == i + 1) {
            wattron(win, A_REVERSE);
            mvwprintw(win, y, x + 2, "%s", choices[i]);
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, y, x + 2, "%s", choices[i]);
        }
        // change position
    }
    wrefresh(win);
}


/* 
* start_program: starts the program
*
* returns: an bool that signifies if yes or no was chosen and whether to 
*           continue execution or quit 
*/
int start_program() {

    int highlight = 1; // move back to main?
    int choice = 0;

    /* yes no option for user input */
    char *yes_no_choice[] = {
        "Yes",
        "No"
    };

    print_by_char(stdscr, "Hi!");
    printw("~\\(≧▽≦)/~\n");
    delay_output(100);
    print_by_char(stdscr, "Are you ready to get started?\n");
    print_yn_menu(stdscr, highlight, yes_no_choice);

    while(1){
        int c = getch();

        switch (c) {
            case KEY_RIGHT:
                if (highlight == 1) {
                    highlight = 2;
                } else {
                    highlight = 1;
                }
                
                break;
            case KEY_LEFT:
                if (highlight == 1) {
                    highlight = 2;
                } else {
                    highlight = 1;
                }
                break;
            case 10:
                choice = highlight;
                break;
            default:
                // mvprintw(10, 0, "Invalid character press");
                // refresh();
                break;
        }
        int x, y;
        getyx(stdscr, y, x);
        move(y, 0);
        print_yn_menu(stdscr, highlight, yes_no_choice);
        if (choice != 0) {
            clear();
            move(0, 0);
        }
        if (choice == 1) {
            printw("Yay!\n");
            break;
        } else if (choice == 2) {
            printw("Ok, goodbey!\n");
            break;
        }
    }

    refresh();
    return (choice == 1);
}

