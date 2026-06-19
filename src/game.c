#include "snake.h"

//Detect to detect which arrow button is pressed and change teh position of the snake.
static void detect_arrows(snake_t *snake, body_t *list)
{
    getch();
    char arrow = getch();
    for (; list; list = list->next) {
        switch (arrow) {
            case 'A' :
                snake->last_move = UP;
                move_snake(list, snake);
                if (!list->prev)
                    list->c = '^';
                break;
            case 'B' :
                snake->last_move = DOWN;
                move_snake(list, snake);
                if (!list->prev)
                    list->c = 'v';
                break;
            case 'C' :
                snake->last_move = RIGHT;
                move_snake(list, snake);
                if (!list->prev)
                    list->c = '>';
                break;
            case 'D' :
                snake->last_move = LEFT;
                move_snake(list, snake);
                if (!list->prev)
                    list->c = '<';
                break;
            default :
                break;
        }
    }
}

//Detect if an apple is eat by the snake. If true, create a new member in the snake tail.
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
                new->pos[POS_X] = snake->body->pos[POS_X] - 1;
                if (new->pos[POS_X] > snake->screen[WIDTH])
                    new->pos[POS_X] = 0;
                new->pos[POS_Y] = snake->body->pos[POS_Y];
                break;
            case DOWN :
                new->pos[POS_X] = snake->body->pos[POS_X] + 1;
                if (new->pos[POS_X] < 0)
                    new->pos[POS_X] = snake->screen[WIDTH];
                new->pos[POS_Y] = snake->body->pos[POS_Y];
                break;
            case RIGHT :
                new->pos[POS_Y] = snake->body->pos[POS_Y] - 1;
                if (new->pos[POS_Y] < 0)
                    new->pos[POS_Y] = snake->screen[HEIGHT];
                new->pos[POS_X] = snake->body->pos[POS_X];
                break;
            case LEFT :
                new->pos[POS_Y] = snake->body->pos[POS_Y] + 1;
                if (new->pos[POS_Y] > snake->screen[HEIGHT])
                    new->pos[POS_Y] = 0;
                new->pos[POS_X] = snake->body->pos[POS_X];
        }
        new->prev = snake->body;
        if (snake->body)
            snake->body->next = new;
        snake->body = new;
        for (; snake->body && snake->body->prev; snake->body = snake->body->prev);
    }
}

//Detect if the snake head enter in collision with the body.
int detect_snake_tail(snake_t *snake)
{
    if (!snake->body->next)
        return false;
    for (body_t *body = snake->body->next; body; body = body->next) {
        if (snake->body->pos[POS_X] == body->pos[POS_X] && snake->body->pos[POS_Y] == body->pos[POS_Y])
            return true;
    }
    return false;
}

//Game loop function to make the Snake game works.
void game_loop(snake_t *snake)
{
    initscr();
    start_color();
    curs_set(0);
    noecho();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    timeout(100);
    while (1) {
        get_terminal_size(snake);
        gettimeofday(&snake->start, NULL);
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(snake->apple->pos[POS_Y], snake->apple->pos[POS_X], "%c", snake->apple->c);
        attroff(COLOR_PAIR(1));
        for (body_t *list = snake->body; list; list = list->next) {
            move_snake(list, snake);
            attron(COLOR_PAIR(2));
            mvprintw(list->pos[POS_Y], list->pos[POS_X], "%c", list->c);
            attroff(COLOR_PAIR(2));
        }
        apple_eat(snake);
        switch (getch()) {
            case 'q' :
                exit_window();
                return;
            case '\033' :
                detect_arrows(snake, snake->body);
                apple_eat(snake);
                break;
        }
        if (detect_snake_tail(snake) == true) {
            exit_window();
            printf(RED"GAME OVER\n"WHITE"Be careful, don't bite your own tail !\n");
            return;
        }
        refresh();
        gettimeofday(&snake->start, NULL);
    }
    exit_window();
}