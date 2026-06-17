#include "snake.h"

//Make the snake move in the given direction.
void move_snake(body_t *elem, move_t last_move, int screen_width, int screen_height)
{
    switch (last_move) {
        case UP :
            elem->pos[POS_Y]--;
            if (elem->pos[POS_Y] < 0)
                elem->pos[POS_Y] = screen_height- 1;
            break;
        case DOWN :
            elem->pos[POS_Y]++;
            if (elem->pos[POS_Y] > screen_height)
                elem->pos[POS_Y] = 0;
            break;
        case RIGHT :
            elem->pos[POS_X]++;
            if (elem->pos[POS_X] > screen_width)
                elem->pos[POS_X] = 0;
            break;
        case LEFT :
            elem->pos[POS_X]--;
            if (elem->pos[POS_X] < 0)
                elem->pos[POS_X] = screen_width - 1;
            break;
        default :
            break;
    }
}