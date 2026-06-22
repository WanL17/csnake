#include "snake.h"

// Creates a new apple n the apple list.
void create_apple(snake_t *snake) {
    body_t *new = calloc(1, sizeof(body_t));

    if (!new)
    	return;
  	new->c = '@';
    srand(time(NULL));
  	new->pos[POS_X] = (rand() % snake->screen[0]);
  	new->pos[POS_Y] = (rand() % snake->screen[1]);
  	for (; snake->apple && snake->apple->next; snake->apple = snake->apple->next);
  	new->prev = snake->apple;
  	new->next = NULL;
  	if (snake->apple)
    	snake->apple->next = new;
  	snake->apple = new;
  	for (; snake->apple && snake->apple->prev; snake->apple = snake->apple->prev);
}

// Detect if an apple is eat by the snake. If true, create a new member in the
// snake tail.
void apple_eat(snake_t *snake) {
  	body_t *new = NULL;
  	body_t *prev = snake->body;

  	for (body_t *apples = snake->apple; apples; apples = apples->next) {
    	if (snake->body->pos[POS_X] == apples->pos[POS_X] &&
        	snake->body->pos[POS_Y] == apples->pos[POS_Y]) {
      		snake->score += 100;
			srand(time(NULL));
			apples->pos[POS_X] = (rand() % snake->screen[0]);
			apples->pos[POS_Y] = (rand() % snake->screen[1]);
			new = create_body('o', false, snake);
			if (!new)
				return;
			for (; snake->body && snake->body->next; snake->body = snake->body->next);
			switch (snake->last_move) {
				case UP:
					new->pos[POS_X] = snake->body->pos[POS_X] - 1;
					if (new->pos[POS_X] > snake->screen[WIDTH])
						new->pos[POS_X] = 0;
					new->pos[POS_Y] = snake->body->pos[POS_Y];
					break;
				case DOWN:
					new->pos[POS_X] = snake->body->pos[POS_X] + 1;
					if (new->pos[POS_X] < 0)
						new->pos[POS_X] = snake->screen[WIDTH];
					new->pos[POS_Y] = snake->body->pos[POS_Y];
					break;
				case RIGHT:
					new->pos[POS_Y] = snake->body->pos[POS_Y] - 1;
					if (new->pos[POS_Y] < 0)
						new->pos[POS_Y] = snake->screen[HEIGHT];
					new->pos[POS_X] = snake->body->pos[POS_X];
					break;
				case LEFT:
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
			return;
    	}
  	}
}
