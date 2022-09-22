/* Functions to execute actions related to study sets */

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "studyset.h"
#include "gui.h"

/*
* new_study_set : promots the user with instructions to create a new study set
*                 and adds the corresponding set to the file of study sets
*/
void new_study_set() {

    /* change settings so user can see what they enter */
    echo();  
    nocbreak();
    char file_name[MAX_FILE_NAME_LENGTH];
    char file[MAX_FILE_NAME_LENGTH + 4];

    printw("%s%s%s", "NOTE: All files must be .txt and formatted such that each ",
     "vocab term is on it\'s own line and terminated by a newline in the ",
     "format:\n\"汉子 - English\"\n");
    printw("Enter the filename in the box below.\n");
    refresh();

    WINDOW *enter_name = create_input_box (60);
    wgetstr(enter_name, file_name);
    noecho();
    cbreak();
    delwin(enter_name);
    clear();

    FILE *study_set;
    sprintf(file, "%s.txt", file_name);

    /* file does not exists */
    study_set = fopen(file, "r");
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

    FILE *study_sets;
    study_sets = fopen("study_sets.txt", "a");
    fprintf(study_sets, "%s\n", file_name);
    fclose(study_sets);

    printw("Study set added!\n\n");
    printw("Press any charcter to return to the main menu.\n");
    getch();
    clear();
    print_menu(FALSE, 0);

}

/*
* review: allows the user to review all the terms in the given study set 
*         by generating a question/answer mechanism
*
* filename: the name of the file for the corresponding studyset (w/o ".txt")
*/
void review(char *filename) {

    char file[MAX_FILE_NAME_LENGTH + 4];  // + 4 to account for ".txt"
    sprintf(file, "%s.txt", filename);
    
    int num_terms;
    char **terms = file_to_array(file, FALSE, &num_terms);

    /* shuffle the array */   
    srand(time(NULL));
    char *swap;
    for (int i = 0; i < num_terms; i++) {
        swap = terms[i];
        int random_index = rand() % num_terms;
        terms[i] = terms[random_index];
        terms[random_index] = swap;

    }  

    echo();
    char answer[MAX_CHAR_LENGTH];

    /* create input box */
    int y, x;
    getyx(stdscr, y, x);
    WINDOW *enter_answer = newwin(3, 20, 3, 0);
    keypad(enter_answer, TRUE);

    int num_correct = 0;

    /* generate questions */
    for (int i = 0; i < num_terms; i++) {
        char character[MAX_CHAR_LENGTH];
        char term[MAX_TERM_LENGTH];
        sscanf(terms[i], "%s - %[^-]s", character, term);

        printw("What is the 汉子 for...\n");
        print_by_char(stdscr, term);
        printw("\n\n");
        refresh();

        box(enter_answer, 0, 0);
        mvwprintw(enter_answer, 1, 2, "");  // move cursor into the box
        refresh();

        wgetstr(enter_answer, answer);

        wclear(enter_answer);
        clear();

        start_color();
        use_default_colors();
        init_color(COLOR_RED, 900, 0, 0);
        init_color(COLOR_GREEN, 0, 800, 0);
        init_pair(1, COLOR_GREEN, -1);  // green for correct answers
        init_pair(2, COLOR_RED, -1);  // red for incorrect answers

        if (strcmp(answer, character) == 0) {
            num_correct++;
            printw("Correct!\n");
            attron(COLOR_PAIR(1));
            printw("%s\n", terms[i]);
            attroff(COLOR_PAIR(1));
            printw("Press enter to move on to the next term");
        } else {
            printw("Incorrect :(\n");
            delay_output(100);
            print_by_char(stdscr, "Good try but the actual answer was...\n\n");
            attron(COLOR_PAIR(2));
            printw("%s\n", terms[i]);
            attroff(COLOR_PAIR(2));
            refresh();
            delay_output(800);
            printw("Press enter to move on to the next term");
        }

        refresh();
            
        while (1) {
            char c = getch();
            if (c == 10) {
                break;
            }
        }
        clear();

    }

    free_array(terms, num_terms);
    delwin(enter_answer);
    printw("All done!\n\n");
    printw("You got %d out of %d correct\n\n", num_correct, num_terms);
    printw("Press any character to return to the main menu\n");
    refresh();
    getch();
    clear();
    print_menu(FALSE, 0);
}

/*
* file_to_array: takes a file and converts it into an array where each index
*                referernces one line of the file
*
* file: the file to be converted
* menu_opt: a boolean that indicates whether the file is being converted into an
*           array to display the menu options (TRUE) or to hold study set terms
*           (FALSE)
* num_terms: the number of terms (lines) in the file
*
* return: an array of strings representing each line of the file
*
*/
char **file_to_array(char *file, bool menu_opt, int *num_terms) {

    FILE *fp;

    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "file_to_array: could not open file");
        exit(1);
    }

    *num_terms = 0;
    int c = fgetc(fp);

    while (c != EOF) {
        c = fgetc(fp);
        if (c == '\n') {
            (*num_terms)++;
        }
    }

    fclose(fp);

    /* create array of study terms */
    if (menu_opt) {
        (*num_terms)++;
    }

    char **terms = (char**)malloc(sizeof(char*) * (*num_terms));
    if (terms == NULL) {
        fprintf(stderr, "file_to_array: memory could not be allocated;");
        exit(1);
    }

    /* reopen file in order to reset cursor position */
    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "file_to_array: could not allocate space");
        exit(1);
    }

    int max;
    if (menu_opt) {
        max = MAX_FILE_NAME_LENGTH;
    } else {
        max = MAX_LINE_LENGTH;
    }

    /* initialize array */
    for (int i = 0; i < (*num_terms); i++) {
        char str[max];
        fgets(str, max + 1, fp);
        if (menu_opt) {
            char intermediate[max + 2];  // +2 for "> "
            sprintf(intermediate, "> %s", str);
            terms[i] = strdup(intermediate);
        } else {
            terms[i] = strdup(str);
        }
    }  

    if (menu_opt) {
        terms[*num_terms - 1] = strdup("> Return to main menu");
    }

    fclose(fp);
    return terms;
}

/*
* free_array: frees an array of strings dynmically allocated
* 
* array: the array to be freed
* num_terms: the number of terms in teh array
*/
void free_array(char **array, int num_terms) {
    for (int i = 0; i < num_terms; i++) {
        free(array[i]);
    }
    free(array);
}


