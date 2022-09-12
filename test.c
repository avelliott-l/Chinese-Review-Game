#include <ncurses.h>

int main() {
    initscr();
    noecho();
    cbreak();

    int y, x;
    getmaxyx(stdscr, y, x);
    printw("y: %d\nx: %d\n", y, x);
    printw("lines: %d\ncols: %d\n", LINES, COLS);
    int height = y / 2;
    WINDOW *win;
    win = newwin(height, 20, (y - height)/2, (x - 20)/2);
    box(win, 0, 0);
    //refresh();
    wrefresh(win);
    wgetch(win);

    endwin();
}