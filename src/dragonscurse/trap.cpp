#include "trap.h"

bool Trap::set_hit(Object *object, Status *status)
{
    Monster::set_hit(object, status);
    set_invinsible(true);
}

void Trap::move(Map *map)
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

