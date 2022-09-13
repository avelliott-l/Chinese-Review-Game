#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "gui.h"
#include "studyset.h"


/*
* print_menu: prints the menu window onto the terminal,
*            allows the user to select an option, and runs 
*            the corresponding code
*
*/
void print_menu(bool return_to_submenu, int choice) {

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

    /* create main menu */
    int height = 11;
    int width = 30;
    int startx = (COLS - width) / 2;
    int starty = (LINES - height) / 2;
    int highlight = 1;
    // int choice = 0;  // keep track of which menu option is chosen

    WINDOW *menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);

    if (!return_to_submenu) {
        char *menu_header = "☆ ~~ MAIN MENU ~~ ☆";
        move(2, 0);
        print_by_char(stdscr, "> What would you like to do today?");
        print_submenu(menu_win, n_choices, highlight, menu_choices, 3, 6, menu_header, &choice);    
    }
    


    if (choice == 1) {  // Review

    } else if (choice == 2) {  // Quiz me!

    } else if (choice == 3) {  // Add a study set
        char *add_choices[] = {
            "> Read from file",
            "> Add manually",
            "> Return to main menu"
        };
        char *header = "☆ Add a new study set ☆";
        n_choices = sizeof(add_choices) / sizeof(char*);
        choice = 0;
        clear();
        print_submenu(menu_win, n_choices, highlight, add_choices, 4, 3, header, &choice);

        if (choice == 1) {  // Read from file
            //wclear(menu_win);
            delwin(menu_win);
            clear();
            new_study_set();

        } else if (choice == 2) {  // Add manually

        } else if (choice == 3) {  // Return to main menu
            delwin(menu_win);
            clear();
            print_menu(FALSE, 0);

        };

    } else if (choice == 4) {  // View a study set

    } else if (choice == 5) {  // Delete a study set

    } else if (choice == 6) {  // Exit
        delwin(menu_win);
        clear();
        print_by_char(stdscr, "Goodbye");
        printw("  _(:з」∠)_");
        printw("\n\nPress any key to quit");
        getch();
    } 
    
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

/* 
* start_program: starts the program
*
* cont: an out parameter that indicates if they program should continue
*
* returns: an bool that signifies if yes or no was chosen and whether to 
*           continue execution or quit 
*/
void start_program(bool *cont) {

    keypad(stdscr, TRUE);

    int highlight = 1; // move back to main?
    int choice = 0;

    /* yes no option for user input */

    print_by_char(stdscr, "Hi! ");
    printw("~\\(≧▽≦)/~\n");
    delay_output(100);
    print_by_char(stdscr, "Are you ready to get started?\n");
    print_yn_menu(stdscr, highlight, &choice);

        if (choice == 1) {
            printw("Yay!\n");
            print_by_char(stdscr, "Let's get started!  ");
            printw("~\\(≧▽≦)/~\n");
            //print_by_char(stdscr, "What would you like to do today?");
        } else if (choice == 2) {
            printw("Ok, goodbye!\n");
            printw("\n\nPress any key to quit");
            getch();
        }


    if (choice == 1) {
        *cont = TRUE;
    } 

    refresh();
    keypad(stdscr, FALSE);

    return;
}

void print_submenu(WINDOW *menu_win, int n_choices, int highlight, char **choices, int height, int header_pos, char *header, int *choice){

    refresh();
    int x = 2;  // distance of menu options from border

    box(menu_win, 0, 0);
    mvwprintw(menu_win, 1, header_pos, "%s", header);
    keypad(menu_win, TRUE);

    while(1) {

        int y = height;
        for (int i = 0; i < n_choices; i++) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        y++;
        }

        wrefresh(menu_win); //

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
                *choice = highlight;
                break;
            default:
                // ADD CONTROLS!!
                break;
        }
        
        if (*choice != 0) {
            break;
        }

    }
    wclear(menu_win);
}


void print_yn_menu(WINDOW *win, int highlight, int *choice){

    char *choices[] = {
        "Yes",
        "No"
    }; 

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
                *choice = highlight;
                break;
            default:
                // mvprintw(10, 0, "Invalid character press");
                // refresh();
                break;
        }
        if (*choice == 0) {
            int x, y;
            getyx(stdscr, y, x);
            move(y, 0);
            print_yn_menu(stdscr, highlight, choice);
        } else {
            clear();
            move(0, 0);
        }
        
}


        