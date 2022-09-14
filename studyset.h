/*
*
*
*
*/

#ifndef STUDYSET
#define STUDYSET

#define MAX_FILE_NAME_LENGTH 50

void new_study_set();

void review(char *filename);

char **file_to_array(char *file, int max_line_length, bool menu_opt, int *num_terms);

#endif