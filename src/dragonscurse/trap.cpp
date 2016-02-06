#include "trap.h"

bool Trap::set_hit(Object *object, Status *status)
{
    Monster::set_hit(object, status);
    set_invinsible(true);
}

void Trap::move(Map *map)
{
    Monster::move(map);

    if (m_action == Still) {
        set_invinsible(false);
    }
}

