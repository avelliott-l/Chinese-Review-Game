#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <locale.h>

void print_by_char(WINDOW *sx, char *);
void print_yn_menu(WINDOW *win, int highlight);

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

/* yes no option for user input */
char *yes_no_choice[] = {
    "Yes",
    "No"
};


int main(){

    int highlight = 1;
    int choice = 0;

    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    keypad(stdscr, TRUE);


    print_by_char(stdscr, "Hi!");
    printw("~\\(≧▽≦)/~\n");
    delay_output(100);
    print_by_char(stdscr, "Are you ready to get started?\n");
    print_yn_menu(stdscr, highlight);

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
        print_yn_menu(stdscr, highlight);
        if (choice == 1) {
            mvprintw(y + 1, 0, "Yay!");
            break;
        } else if (choice == 2) {
            mvprintw(y + 1, 0, "Ok, goodbey!");
            break;
        }
    }
    refresh();

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

void print_yn_menu(WINDOW *win, int highlight){
    for (int i = 0; i < 2; i++) {
        int x, y;
        getyx(win, y, x);
        if (highlight == i + 1) {
            wattron(win, A_REVERSE);
            mvwprintw(win, y, x + 2, "%s", yes_no_choice[i]);
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, y, x + 2, "%s", yes_no_choice[i]);
        }
        // change position
    }
    wrefresh(win);
}