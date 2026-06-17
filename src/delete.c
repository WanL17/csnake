#include "snake.h"

void free_snake(snake_t *snake)
{
    if (!snake)
        return;
    if (snake->body) {
        while (snake->body) {
            body_t *tmp = snake->body;
            snake->body = snake->body->next;
            free(tmp);
        }
    }
    if (snake->apple)
        free(snake->apple);
    free(snake);
}