#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "studyset.h"
#include "gui.h"
#define MAX_LINE_LENGTH 100
#define MAX_TERM_LENGTH 90
#define MAX_CHAR_LENGTH 10
// CHANGE: declare man file name length instead of use 50

// add manually or import file
/*
* new_study_set : promots the user with instructions to create a new study set
*/
void new_study_set() {

    /* change settings so user can see what they enter */
    echo();  
    nocbreak();
    char file_name[MAX_FILE_NAME_LENGTH];
    char file[MAX_FILE_NAME_LENGTH + 4];

    printw("%s%s", "NOTE: All files must be .txt and formatted such that each ",
     "vocab term is on it\'s own line in the format:\n\"English | 汉子\"\n");
    printw("Enter the filename in the box below.\n");
    refresh();

    // /* create input box */
    // int y, x;
    // getyx(stdscr, y, x);
    // WINDOW *enter_name = newwin(3, 60, y, x);
    // box(enter_name, 0, 0);

    // mvwprintw(enter_name, 1, 2, ""); // move cursor into the box

    WINDOW *enter_name = create_input_box (60);
    wgetstr(enter_name, file_name);
    noecho();
    cbreak();
    delwin(enter_name);
    clear();

    FILE *study_set;
    sprintf(file, "%s.txt", file_name);

    // clear if file exists

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
    // open file for append
    // later make array to print menu


    printw("Study set added!\n\n");
    printw("Press any charcter to return to the main menu.\n");
    // add study set to sub menu for review
    getch();
    clear();
    print_menu(FALSE, 0);

}

void review(char *filename) {


    char file[MAX_FILE_NAME_LENGTH + 4];  // + 4 to account for ".txt"
    sprintf(file, "%s.txt", filename);

    printw("file: %s", file);
    refresh();
    getch();
    
    int num_terms;
    //char *terms[] = file_to_array(fp, MAX_LINE_LENGTH, FALSE, &num_terms);
    char **terms = file_to_array(file, MAX_LINE_LENGTH, FALSE, &num_terms);

    printw("here");
    refresh();
    getch();

    /* shuffle the array */   
    srand(time(NULL));
    char *swap;
    for (int i = 0; i < num_terms; i++) {
        swap = terms[i];
        int random_index = rand() % num_terms;
        terms[i] = terms[random_index];
        terms[random_index] = swap;

    }  

    printw("here");
    refresh();
    getch();

    echo();
    //printw("What is the 汉子 for...\n");
    char answer[MAX_CHAR_LENGTH];
    //WINDOW *enter_answer = create_input_box(20);

    /* create input box */
    int y, x;
    getyx(stdscr, y, x);
    WINDOW *enter_answer = newwin(3, 20, y, x);


    for (int i = 1; i < num_terms; i++) {
        char character[MAX_CHAR_LENGTH];
        char term[MAX_TERM_LENGTH];
        sscanf(terms[i], "%s | %s", term, character);

        printw("What is the 汉子 for...\n");
        print_by_char(stdscr, term);
        printw("\n\n");

        box(enter_answer, 0, 0);
        mvwprintw(enter_answer, 1, 2, "");

        wgetstr(enter_answer, answer);

        wclear(enter_answer);
        clear();

        if (strcmp(answer, character) == 0) {
            printw("Correct!\n");
            printw("s", terms[i]);
            printw("Press enter to move on to the next term");
        } else {
            printw("Incorrect :(\n");
            delay_output(100);
            printw("Good try but the actual answer was...\n");
            // print characters in red
            // print term | the char w/ attr on
            printw("s", terms[i]);
            delay_output(200);
            printw("Press enter to move on to the next term");

        }
            
        while (1) {
            char c = getch();
            if (c == 10) {
                break;
            }
        }
        clear();

    }

    printw("All done\n");
    getch();
        
}

char **file_to_array(char *file, int max_line_length, bool menu_opt, int *num_terms) {
    
    //fopen(fp, "r");
    FILE *fp;

    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "file_to_array: could not allocate space");
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

    //char *terms[*num_terms];

    char **terms = (char**)malloc(sizeof(char*) * (*num_terms));
    if (terms == NULL) {
        fprintf(stderr, "file_to_array: memory could not be allocated;");
        exit(1);
    }

    // need to free
    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "file_to_array: could not allocate space");
        exit(1);
    }


    for (int i = 0; i < (*num_terms - 1); i++) {
        char str[MAX_FILE_NAME_LENGTH];
        fgets(str, max_line_length, fp);
        if (menu_opt) {
            char intermediate[MAX_FILE_NAME_LENGTH + 2];  // +2 for "> "
            sprintf(intermediate, "> %s", str);
            terms[i] = strdup(intermediate);
        } else {
            terms[i] = strdup(str);
        }
        // need to free
    }  

    printw("terms[0]: %s", terms[0]);
    refresh();
    getch();

    if (menu_opt) {
        terms[*num_terms - 1] = "> Return to main menu";
    }

    printw("here3");
    refresh();
    getch();

    fclose(fp);

    printw("here3");
    refresh();
    getch();

    return terms;

}


