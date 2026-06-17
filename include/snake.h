#ifndef SNAKE_H
    #define SNAKE_H
    #define _GNU_SOURCE

    #include <unistd.h>
    #include <ncurses.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <time.h>
    #include <sys/time.h>
    #include <sys/ioctl.h>

    #define POS_X 0
    #define POS_Y 1
    #define WIDTH 0
    #define HEIGHT 1

typedef enum move_s {
    UP,
    RIGHT,
    LEFT,
    DOWN
} move_t;

typedef struct body_s {
    char c;
    int pos[2];
    struct body_s *prev;
    struct body_s *next;
} body_t;

typedef struct snake_s {
    move_t last_move;
    int score;
    int screen[2];
    body_t *body;
    body_t *apple;
    struct timeval start;
    struct timeval end;
} snake_t;

void get_terminal_size(snake_t *snake);
void exit_window(void);
void free_snake(snake_t *snake);
body_t *create_body(char c, int apple, snake_t *snake);
void move_snake(body_t *elem, move_t last_move, int screen_width, int screen_height);
void game_loop(snake_t *snake);
int main(int argc, char **argv);

#endif