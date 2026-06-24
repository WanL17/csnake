#include "snake.h"

void main_menu(snake_t *snake)
{
    while (1) {
        clear();
        mvprintw(LINES / 2 - 5, COLS / 2 - 15, "oooooooooooooooooooooooooooooo");
        mvprintw(LINES / 2, COLS / 2 - 17, "o");
        mvprintw(LINES / 2 - 1, COLS / 2 - 18, "o");
        mvprintw(LINES / 2 - 2, COLS / 2 - 18, "o");
        mvprintw(LINES / 2 - 3, COLS / 2 - 17, "o");
        mvprintw(LINES / 2 - 4, COLS / 2 - 16, "o");
        mvprintw(LINES / 2 - 4, COLS / 2 + 15, "o");
        mvprintw(LINES / 2 - 3, COLS / 2 + 16, "v");
        mvprintw(LINES / 2, COLS / 2 - 5, "* CSNAKE *");
        mvprintw(LINES - 1, 0, "Press Q to quit the game. Press ENTER to start the game.");
        refresh();
        switch (getch()) {
            case '\n' :
                return;
            case 'q' :
                exit_window();
                free_snake(snake);
                exit(EXIT_SUCCESS);
        }
    }
}

void pause_menu(snake_t *snake)
{
    while (1) {
        clear();
        mvprintw(LINES / 2, COLS / 2, "PAUSE");
        mvprintw(LINES - 1, 0, "Press Q to quit the game. Press E to return to the game.");
        mvprintw(LINES - 1, COLS - 20, "Your score: %i", snake->score);
        refresh();
        switch (getch()) {
            case 'e' :
                return;
            case 'q' :
                exit_window();
                free_snake(snake);
                exit(EXIT_SUCCESS);
        }
    }
}

void game_over_screen(snake_t *snake)
{
    int score = snake->score;
    while (1) {
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(LINES / 2, COLS / 2 - 5, "GAME OVER");
        attroff(COLOR_PAIR(1));
        mvprintw(LINES / 2 + 1, COLS / 2 - 10, "Your score: %i", score);
        mvprintw(LINES - 1, 0, "Press Q to quit the game.");
        refresh();
        if (getch() == 'q')
            exit_window();
    }
}