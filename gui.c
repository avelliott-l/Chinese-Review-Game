/* Functions to implement the GUI */

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
*  return_to_submenu: a boolean value which is true us this function is called      
*                     return to a submenu, and false if this function is called 
*                     to return to the main menu
*  choice: an integer indicating which menu option has been chosen -- always set
*          to 0 if returning to main menu, if returning to submenu has a postive
*          value
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

    WINDOW *menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);

    /* create main menu */
    if (!return_to_submenu) {
        char *menu_header = "☆ ~~ MAIN MENU ~~ ☆";
        move(2, 0);
        print_by_char(stdscr, "> What would you like to do today?");
        print_menu_helper(menu_win, n_choices, highlight, menu_choices, 3, 6, 
                          menu_header, &choice);    
    }

    if (choice == 1) {  // Review

        /* create array to menu choices to print to menu */
        char study_sets[] = "study_sets.txt";
        int n_choices;
        char **study_set_options = file_to_array(study_sets, TRUE, &n_choices);
        char *header = "☆ Pick a set ☆";
        int header_pos = 6;
        
        if (n_choices == 1) {
            header = "~No sets study sets added~";
            header_pos = 2;
        }

        choice = 0;
        clear();

        print_menu_helper(menu_win, n_choices, highlight, study_set_options, 3, 
                          header_pos, header, &choice);

        char *chosen = study_set_options[choice - 1];

        /* return to main menu */
        if (strcmp(chosen, "> Return to main menu") == 0) { 
            delwin(menu_win);
            clear();
            print_menu(FALSE, 0);

        /* open the selected study set for review */
        } else {  
            char filename[MAX_FILE_NAME_LENGTH + 4];
            sscanf(chosen, "> %s", filename);
            delwin(menu_win);
            clear();
            review(filename);
            free_array(study_set_options, n_choices);
        }

    } else if (choice == 2) {  // Quiz me!
        printw("\n Function not yet implemented. Please choose again.");
        refresh();
        delay_output(1500);
        clear();
        print_menu(FALSE, 0);

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
        print_menu_helper(menu_win, n_choices, highlight, add_choices, 4, 3, header, &choice);

        if (choice == 1) {  // Read from file
            //wclear(menu_win);
            delwin(menu_win);
            clear();
            new_study_set();

        } else if (choice == 2) {  // Add manually
            printw("\n Function not yet implemented. Please choose again.");
            refresh();
            delay_output(1500);
            clear();
            print_menu(TRUE, 3);

        } else if (choice == 3) {  // Return to main menu
            delwin(menu_win);
            clear();
            print_menu(FALSE, 0);

        };

    } else if (choice == 4) {  // View a study set
        printw("\n Function not yet implemented. Please choose again.");
        refresh();
        delay_output(1500);
        clear();
        print_menu(FALSE, 0);

    } else if (choice == 5) {  // Delete a study set
        printw("\n Function not yet implemented. Please choose again.");
        refresh();
        delay_output(1500);
        clear();
        print_menu(FALSE, 0);

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
* start_program: starts the program
*
* cont: an out parameter that indicates if they program should continue
*
*/
void start_program(bool *cont) {

    keypad(stdscr, TRUE);

    int highlight = 1;
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
*/
void print_menu_helper(WINDOW *menu_win, int n_choices, int highlight, char **choices, int height, int header_pos, char *header, int *choice) {

    refresh();
    int x = 2;  // distance of menu options from border

    /* print menu */
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
        y++;  // change height so each menu option prints below the last
        }

        wrefresh(menu_win);

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

/*
* print_yn_menu: prints a yes/no answer prompt for the use
*
* win: the window to be printed on
* highlight: an int indicating which option is selected
* choice: an out parameter indicating which option was chosen
*/
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
                // ADD CONTROLS
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
        delay_output(50);
        refresh();
    }
}

/*
* create_input_box: creates a box for user input
*
* width: width of box
*
* returns: a pointer to a window that contains the box
*/
WINDOW *create_input_box(int width) {
    int y, x;
    getyx(stdscr, y, x);
    WINDOW *win = newwin(3, width, y, x);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "");  // move cursor into the box
    return win;
}
        