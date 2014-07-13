#include "phoboz/ctrl.h"
#include "area.h"
#include "church.h"

Church::Church(const char *image, MediaDB *media, int sx, int sy)
    : Room(image, "Wonderfull_18", media, sx, sy, 80, 312)
{
    m_text->add_text("Welcome to church\nsave your progress?");
    m_menu = new Menu("Wonderfull_18", media);
    m_menu->add_option("Yes");
    m_menu->add_option("No");
}

Area* Church::move()
{
    int input = get_input();
    if (input & PRESS_JUMP) {
        return new Area("village.tmx", m_sx, m_sy);
    }

    return 0;
}

void Church::draw(SDL_Surface *dest, int x, int y,
                  int clip_x, int clip_y, int clip_w, int clip_h)
{
    Room::draw(dest, x, y, clip_x, clip_y, clip_w, clip_h);
    m_menu->draw(dest, x + 80, y + 360, clip_x, clip_y, clip_w, clip_h);
}

