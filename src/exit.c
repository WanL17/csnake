#include "snake.h"

//Make the program leave the ncurses window.
void exit_window()
{
    nocbreak();
    echo();
    curs_set(1);
    endwin();
}