#include "snake.h"

//Make the snake move in the given direction.
void move_snake(body_t *elem, snake_t *snake)
{
    if (!elem->prev) {
        elem->prev_pos[POS_X] = elem->pos[POS_X];
        elem->prev_pos[POS_Y] = elem->pos[POS_Y];  
        switch (snake->last_move) {
            case UP :
                elem->pos[POS_Y]--;
                if (elem->pos[POS_Y] < 0)
                    elem->pos[POS_Y] = snake->screen[HEIGHT]- 1;
                break;
            case DOWN :
                elem->pos[POS_Y]++;
                if (elem->pos[POS_Y] > snake->screen[HEIGHT])
                    elem->pos[POS_Y] = 0;
                break;
            case RIGHT :
                elem->pos[POS_X]++;
                if (elem->pos[POS_X] > snake->screen[WIDTH])
                    elem->pos[POS_X] = 0;
                break;
            case LEFT :
                elem->pos[POS_X]--;
                if (elem->pos[POS_X] < 0)
                    elem->pos[POS_X] = snake->screen[WIDTH] - 1;
                break;
            default :
                break;
        }
    } else {
        elem->prev_pos[POS_X] = elem->pos[POS_X];
        elem->prev_pos[POS_Y] = elem->pos[POS_Y];  
        elem->pos[POS_X] = elem->prev->prev_pos[POS_X];
        elem->pos[POS_Y] = elem->prev->prev_pos[POS_Y];
    }
}