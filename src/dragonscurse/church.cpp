#include "phoboz/ctrl.h"
#include "area.h"
#include "church.h"

Area* Church::move()
{
    int input = get_input();
    if (input & PRESS_JUMP) {
        return new Area("village.tmx", m_sx, m_sy);
    }

    return 0;
}

