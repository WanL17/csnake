#include "snake.h"

static void display_version()
{
    printf("csnake version 1.0\n");
}

static void display_helper()
{
    printf("csnake 1.0\n\nDESCRIPTION:\nThis is a recreation of the famous game snake fully in C and made for TUI.\n\nUSAGE: csnake [otions]\n\n");
    printf("Options:\n-h\tPrint helper\n-v\tPrint version\n");
}

//Get the terminal window width and height.
void get_terminal_size(snake_t *snake)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    snake->screen[0] = w.ws_col;
    snake->screen[1] = w.ws_row;
}

//Creates the body parts of the snake (head, body, tail).
body_t *create_body(char c, int apple, snake_t *snake)
{
    body_t *elem = calloc(1, sizeof(body_t));

    if (!elem)
        return NULL;
    elem->c = c;
    if (apple == true) {
        srand(time(NULL));
        elem->pos[POS_X] = (rand() % snake->screen[0]);
        elem->pos[POS_Y] = (rand() % snake->screen[1]);
    }
    return elem;
}

//Main function.
int main(int argc, char **argv)
{
    if (argc > 1) {
        if (argc == 2 && strcmp("-h", argv[1]) == 0) {
            display_helper();
            return 0;
        } else if (argc == 2 && strcmp("-v", argv[1]) == 0) {
            display_version();
            return 0;
        } else {
            printf("csnake: too much arguments.\n");
            return 1;
        }
    }
    snake_t *snake = calloc(1, sizeof(snake_t));
    if (!snake)
        return 84;
    snake->delay = 1000;
    snake->last_move = DOWN;
    get_terminal_size(snake);
    snake->body = create_body('v', false, snake);
    snake->apple = create_body('@', true, snake);
    game_loop(snake);
    printf("Your score: "BLUE"%i.\n"WHITE, snake->score);
    free_snake(snake);
    return 0;
}