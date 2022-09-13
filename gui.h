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
void print_menu(bool return_to_submenu, int choice);

void print_yn_menu(WINDOW *win, int highlight, int *choice);

/* 
* start_program: starts the program
*
* cont: an out parameter that indicates if they program should continue
*
* returns: an bool that signifies if yes or no was chosen and whether to 
*           continue execution or quit 
*/
void start_program(bool *cont);

void print_submenu(WINDOW *menu_win, int n_choices, int highlight, char **choices, int height, int header_pos, char *header, int *choice);

#endif