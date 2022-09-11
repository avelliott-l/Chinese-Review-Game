/*
*
*
*
*/

#ifndef GUI_H
#define GUI_H
#include <ncurses.h>

void print_by_char(WINDOW *win, char *string);

/*
* print_menu: prints the menu window onto the terminal
*
* menu_win: pointer to the window terminal
* highlight: a an integer to indicate which choice is selected
*
*/
void print_menu(WINDOW *menu_win, int highlight, char **menu_choices, int n_choices);

void print_yn_menu(WINDOW *win, int highlight, char **choices);

int start_program();

#endif