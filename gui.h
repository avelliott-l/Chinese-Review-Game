/*
*
*
*
*/

#ifndef GUI_H
#define GUI_H
#include <ncurses.h>

/*
* print_by_char: prints a string out character by character to roughly 
*                imitate typing
*
* win: the window the text will be printed onto
* string: the text to be printed out
*
*/
void print_by_char(WINDOW *win, char *string);

/*
* print_menu: prints the menu window onto the terminal,
*            allows the user to select an option, and runs 
*            the corresponding code
*
* return_to_submenu: a boolean value which is true us this function is called      
*                     return to a submenu, and false if this function is called 
*                     to return to the main menu
* choice: an integer indicating which menu option has been chosen -- always set
*          to 0 if returning to main menu, if returning to submenu has a postive
*          value
*
*/
void print_menu(bool return_to_submenu, int choice);

/*
* print_yn_menu: prints a yes/no answer prompt for the use
*
* win: the window to be printed on
* highlight: an int indicating which option is selected
* choice: an out parameter indicating which option was chosen
*/
void print_yn_menu(WINDOW *win, int highlight, int *choice);

/* 
* start_program: starts the program
*
* cont: an out parameter that indicates if they program should continue
*
*/
void start_program(bool *cont);

/*
* print_menu_helper: helper function to print the menu display
*
* menu_win: the window to be printed, 
* n_choices: the number of options in the menu
* highlgiht: an int indicating the menu option selected and thus highlighted
* choices: an array of strings when the menu options
* height: an int indicating where in the window the first option will be printed
* header_pos: an int indicating the x coord of the menu header
* header: a string that is the header for the menu
* choice: an out parameter indicating which menu option is chosen
*
*
*/
void print_menu_helper(WINDOW *menu_win, int n_choices, int highlight, char **choices, int height, int header_pos, char *header, int *choice);

/*
* create_input_box: creates a box for user input
*
* width: width of box
*
* returns: a pointer to a window that contains the box
*/
WINDOW *create_input_box(int width);

#endif