#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <locale.h>

/* function choices for main menu */
char *choices[] = {
    "Review",
    "Quiz me!",
    "Add a new study set",
    "View a study set",
    "Delete a study set",
    "Exit"
};
int n_choices = sizeof(choices) / sizeof(char*);

/* yes no option for user input */
char *yes_no[] = {
    "Yes",
    "No"
};



int main(){
setlocale(LC_ALL, "");
initscr();

print_by_char(stdscr, "Hi! ~\\(≧▽≦)/~\nAre you ready to get started?\n");

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
        delay_output(150);
        refresh();
    }
}