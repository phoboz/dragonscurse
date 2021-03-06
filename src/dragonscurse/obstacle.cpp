#include "obstacle.h"

void Obstacle::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Move:
            animate_move();
            break;

        case Still:
            set_action(Move);
            set_invinsible(false);
            break;
    }
}

