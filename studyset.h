/* Interface for actions related to study sets */

#ifndef STUDYSET
#define STUDYSET
#define MAX_FILE_NAME_LENGTH 50
#define MAX_LINE_LENGTH 100
#define MAX_TERM_LENGTH 90
#define MAX_CHAR_LENGTH 10

/*
* review: allows the user to review all the terms in the given study set 
*         by generating a question/answer mechanism
*
* filename: the name of the file for the corresponding studyset (w/o ".txt")
*/
void new_study_set();

/*
* review: allows the user to review all the terms in the given study set 
*         by generating a question/answer mechanism
*
* filename: the name of the file for the corresponding studyset (w/o ".txt")
*/
void review(char *filename);

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
char **file_to_array(char *file, bool menu_opt, int *num_terms);

/*
* free_array: frees an array of strings dynmically allocated
* 
* array: the array to be freed
* num_terms: the number of terms in teh array
*/
void free_array(char **array, int num_terms);

#endif