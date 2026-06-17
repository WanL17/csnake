#include "snake.h"

//Make the program leave the ncurses window.
void exit_window(void)
{
    echo();
    endwin();
}