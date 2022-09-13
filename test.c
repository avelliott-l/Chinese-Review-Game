#include <ncurses.h>

// int main() {
//     initscr();
//     noecho();
//     cbreak();

//     int y, x;
//     getmaxyx(stdscr, y, x);
//     printw("y: %d\nx: %d\n", y, x);
//     printw("lines: %d\ncols: %d\n", LINES, COLS);
//     int height = y / 2;
//     WINDOW *win;
//     win = newwin(height, 20, (y - height)/2, (x - 20)/2);
//     box(win, 0, 0);
//     //refresh();
//     wrefresh(win);
//     wgetch(win);
//     werase(win);
//     wgetch(win);

//     endwin();
// }

#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 
 
int main()
{
 char mesg[]="Enter a string: \n";		/* message to be appeared on the screen */
 char str[80];
 int row,col;				/* to store the number of rows and *
					 * the number of colums of the screen */
 initscr();				/* start the curses mode */
 getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
 mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
                     		/* print the message at the center of the screen */
 getstr(str);
 mvprintw(LINES - 2, 0, "You Entered: %s", str);
 getch();
 endwin();

 return 0;
}