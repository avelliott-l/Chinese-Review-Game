#include <ncurses.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_FILE_NAME_LENGTH 50
#define MAX_LINE_LENGTH 100
#define MAX_TERM_LENGTH 90
#define MAX_CHAR_LENGTH 10

char **file_to_array(char *file, int max_line_length, bool menu_opt, int *num_terms) {
    
    //fopen(fp, "r");

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
    if ((*num_terms) > 0) {
        (*num_terms)++;
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

    // need to free
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
        // need to free
    }  

    if (menu_opt) {
        terms[*num_terms - 1] = strdup("> Return to main menu");
    }

    fclose(fp);

    return terms;

}


void review(char *filename) {


    char file[MAX_FILE_NAME_LENGTH + 4];  // + 4 to account for ".txt"
    sprintf(file, "%s.txt", filename);
    
    int num_terms;
    char **terms = file_to_array(file, MAX_LINE_LENGTH, FALSE, &num_terms);

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
    //printw("What is the 汉子 for...\n");
    char answer[MAX_CHAR_LENGTH];
    //WINDOW *enter_answer = create_input_box(20);

    /* create input box */
    int y, x;
    getyx(stdscr, y, x);
    WINDOW *enter_answer = newwin(3, 20, 3, 0);
    keypad(enter_answer, TRUE);

    // test
    // idlok(stdscr, TRUE);
    // scrollok(stdscr, TRUE);
    // printw("num_terms: %d\n", num_terms);
    // refresh();
    // getch();
    // for (int i = 0; i < num_terms; i++) {
    //     printw("%s", terms[i]);
    //     refresh();
    //     getch();
    // }
    // clear();


    for (int i = 0; i < num_terms; i++) {
        char character[MAX_CHAR_LENGTH];
        char term[MAX_TERM_LENGTH];
        sscanf(terms[i], "%s - %[^-]s", character, term);
        // sscanf(terms[i], "%[^|]s %s", term, character);
        printw(terms[i]);
        printw("char: %s\n", character);
        printw("term: %s\n", term);
        refresh();
        getch();
        clear();

        printw("What is the 汉子 for...\n");
        printw(term);
        printw("\n\n");
        refresh();

        box(enter_answer, 0, 0);
        mvwprintw(enter_answer, 1, 2, "");
        refresh();

        wgetstr(enter_answer, answer);

        wclear(enter_answer);
        clear();

        if (strcmp(answer, character) == 0) {
            printw("Correct!\n");
            printw("%s\n", terms[i]);
            printw("Press enter to move on to the next term");
        } else {
            printw("Incorrect :(\n");
            delay_output(100);
            printw("Good try but the actual answer was...\n");
            // print characters in red
            // print term | the char w/ attr on
            printw("%s\n", terms[i]);
            delay_output(200);
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

    // free_array(terms, num_terms);
    delwin(enter_answer);
    printw("All done\n");
    refresh();
    getch();
}

// char **file_to_array(char *file, int max_line_length, bool menu_opt, int *num_terms) {
    
//     //fopen(fp, "r");
// 	FILE *fp;
// 	fp = fopen(file, "r");

//     *num_terms = 0;
//     char c;
//     while ((c = fgetc(fp)) != EOF) {
//         if (c == '\n') {
//             (*num_terms)++;
//         }
//     }

//     /* create array of study terms */
//     if (menu_opt) {
//         (*num_terms)++;
//     }

//     //char *terms[*num_terms];
//     char **terms = (char**)malloc(sizeof(char*) * (*num_terms));
//     if (terms == NULL) {
//         fprintf(stderr, "file_to_array: memory could not be allocated;");
//         exit(1);
//     }

//     // need to free

//     for (int i = 0; i < *num_terms; i++) {
//         fgets(terms[i], max_line_length, fp);
//     }  

//     if (menu_opt) {
//         terms[*num_terms] = "> Return to main menu";
//     }

//     fclose(fp);

//     return terms;

// }


// char **file_to_array(char *file, int max_line_length, bool menu_opt, int *num_terms) {
    
//     //fopen(fp, "r");

//     FILE *fp;

//     fp = fopen(file, "r");
//     if (fp == NULL) {
//         fprintf(stderr, "file_to_array: could not open file");
//         exit(1);
//     }

//     *num_terms = 0;
//     int c = fgetc(fp);

//     while (c != EOF) {
//         c = fgetc(fp);
//         if (c == '\n') {
//             (*num_terms)++;
//         }
//     }

//     fclose(fp);

//     /* create array of study terms */
//     if (menu_opt) {
//         (*num_terms)++;
//     }

//     char **terms = (char**)malloc(sizeof(char*) * (*num_terms));
//     if (terms == NULL) {
//         fprintf(stderr, "file_to_array: memory could not be allocated;");
//         exit(1);
//     }

//     // need to free
//     fp = fopen(file, "r");
//     if (fp == NULL) {
//         fprintf(stderr, "file_to_array: could not allocate space");
//         exit(1);
//     }


//     for (int i = 0; i < (*num_terms); i++) {
//         char str[MAX_FILE_NAME_LENGTH];
//         fgets(str, max_line_length, fp);
//         if (menu_opt) {
//             char intermediate[MAX_FILE_NAME_LENGTH + 2];  // +2 for "> "
//             sprintf(intermediate, "> %s", str);
//             terms[i] = strdup(intermediate);
//         } else {
//             terms[i] = strdup(str);
//         }
//         // need to free
//     }  

//     if (menu_opt) {
//         terms[*num_terms - 1] = strdup("> Return to main menu");
//     }

//     printw("here2");
//     refresh();
//     getch();

//     fclose(fp);

//     printw("here3");
//     refresh();
//     getch();

//     return terms;

// }

int main () {
    /* include support for chinese characters */
    setlocale(LC_ALL, "");

    /* start NCURSES */
    initscr();
    clear();
    noecho();
    cbreak();

	review("lesson1");

    endwin();
	return 0;
}
