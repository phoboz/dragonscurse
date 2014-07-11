#include "phoboz/ctrl.h"
#include "area.h"
#include "church.h"

Church::Church(const char *image, MediaDB *media, int sx, int sy)
    : Room(image, "Wonderfull_18", media, sx, sy, 80, 312)
{
    m_text->add_line("Welcome to church, save your progress?");
    m_text->add_line("");
    m_text->add_line("Yes");
    m_text->add_line("No");
}

Area* Church::move()
{
    int input = get_input();
    if (input & PRESS_JUMP) {
        return new Area("village.tmx", m_sx, m_sy);
    }

    return 0;
}

