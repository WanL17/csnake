#include "snake.h"

//Detect to detect which arrow button is pressed and change teh position of the snake.
static void detect_arrows(snake_t *snake, body_t *list)
{
    getch();
    char arrow = getch();
    for (int i = 0; list; list = list->next) {
        switch (arrow) {
            case 'A' :
                snake->last_move = UP;
                move_snake(list, snake->last_move, snake->screen[WIDTH], snake->screen[HEIGHT]);
                if (i == 0)
                    list->c = '^';
                break;
            case 'B' :
                snake->last_move = DOWN;
                move_snake(list, snake->last_move, snake->screen[WIDTH], snake->screen[HEIGHT]);
                if (i == 0) {
                    printf("%i\n", i);
                    list->c = 'v';
                }
                break;
            case 'C' :
                snake->last_move = RIGHT;
                move_snake(list, snake->last_move, snake->screen[WIDTH], snake->screen[HEIGHT]);
                if (i == 0)
                    list->c = '>';
                break;
            case 'D' :
                snake->last_move = LEFT;
                move_snake(list, snake->last_move, snake->screen[WIDTH], snake->screen[HEIGHT]);
                if (i == 0)
                    list->c = '<';
                break;
            default :
                break;
        }
        i++;
    }
}

//Detect if an apple is eat by the snake. If true, create a new member in the snake body.
void apple_eat(snake_t *snake)
{
    body_t *new = NULL;
    body_t *prev = snake->body;

    if (snake->body->pos[POS_X] == snake->apple->pos[POS_X] && snake->body->pos[POS_Y] == snake->apple->pos[POS_Y]) {
        snake->score += 100;
        srand(time(NULL));
        snake->apple->pos[POS_X] = (rand() % snake->screen[0]);
        snake->apple->pos[POS_Y] = (rand() % snake->screen[1]);
        new = create_body('o', false, snake);
        if (!new)
            return;
        for (; snake->body && snake->body->next; snake->body = snake->body->next);
        switch (snake->last_move) {
            case UP :
                new->pos[POS_Y] = snake->body->pos[POS_Y] - 1;
                if (new->pos[POS_Y] > snake->screen[HEIGHT])
                    new->pos[POS_Y] = 0;
                new->pos[POS_X] = snake->body->pos[POS_X];
            case DOWN :
                new->pos[POS_Y] = snake->body->pos[POS_Y] + 1;
                if (new->pos[POS_Y] < 0)
                    new->pos[POS_Y] = snake->screen[HEIGHT];
                new->pos[POS_X] = snake->body->pos[POS_X];
            case RIGHT :
                new->pos[POS_X] = snake->body->pos[POS_X] - 1;
                if (new->pos[POS_X] < 0)
                    new->pos[POS_X] = snake->screen[WIDTH];
                new->pos[POS_Y] = snake->body->pos[POS_Y];
            case LEFT :
                new->pos[POS_X] = snake->body->pos[POS_X] + 1;
                if (new->pos[POS_X] > snake->screen[WIDTH])
                    new->pos[POS_X] = 0;
                new->pos[POS_Y] = snake->body->pos[POS_Y];
        }
        new->prev = snake->body;
        if (snake->body)
            snake->body->next = new;
        snake->body = new;
        for (; snake->body && snake->body->prev; snake->body = snake->body->prev);
    }
}

int detect_snake_tail(snake_t *snake)
{
    if (!snake->body->next)
        return false;
    for (body_t *body = snake->body->next; body; body = body->next) {
        if (snake->body->pos[POS_X] + 1 == body->pos[POS_X] && snake->body->pos[POS_Y] == body->pos[POS_Y] && snake->last_move == RIGHT)
            return true;
        if (snake->body->pos[POS_X] - 1 == body->pos[POS_X] && snake->body->pos[POS_Y] == body->pos[POS_Y] && snake->last_move == LEFT)
            return true;
        if (snake->body->pos[POS_X] == body->pos[POS_X] && snake->body->pos[POS_Y] - 1 == body->pos[POS_Y] && snake->last_move == UP)
            return true;
        if (snake->body->pos[POS_X] == body->pos[POS_X] && snake->body->pos[POS_Y] + 1 == body->pos[POS_Y] && snake->last_move == DOWN)
            return true;
    }
    return false;
}

//Game loop function to make the Snake game works.
void game_loop(snake_t *snake)
{
    initscr();
    curs_set(0);
    noecho();
    timeout(200);
    while (1) {
        get_terminal_size(snake);
        gettimeofday(&snake->start, NULL);
        clear();
        mvprintw(snake->apple->pos[POS_Y], snake->apple->pos[POS_X], "%c", snake->apple->c);
        for (body_t *list = snake->body; list; list = list->next) {
            move_snake(list, snake->last_move, snake->screen[WIDTH], snake->screen[HEIGHT]);
            mvprintw(list->pos[POS_Y], list->pos[POS_X], "%c", list->c);
        }
        apple_eat(snake);
        switch (getch()) {
            case 'q' :
                exit_window();
                return;
            case '\033' :
                detect_arrows(snake, snake->body);
                break;
        }
        if (detect_snake_tail(snake) == true) {
            exit_window();
            printf("Be careful, don't bite your own tail %i!\n", snake->last_move);
            return;
        }
        refresh();
        gettimeofday(&snake->start, NULL);
    }
    exit_window();
}