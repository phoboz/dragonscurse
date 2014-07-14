#include "phoboz/ctrl.h"
#include "area.h"
#include "shop.h"

Shop::Shop(MediaDB *media, int sx, int sy)
    : Room("shop.png", "Wonderfull_18", media, sx, sy, 94, 240)
{
    m_text->add_text("Shoping\n please");
    m_menu = new Menu("Wonderfull_18", "icons.png", 0, media);
    m_menu->set_spacing(80);
    m_menu->add_option("", "icons.png", 1);
    m_menu->add_option("Mithrill\nShiled", "icons.png", 3);
    m_menu->add_option("Mithrill\nArmour", "icons.png", 4);
    m_menu->add_option("");
    m_menu->add_option("Exit");
}

Area* Shop::move(int key)
{
    int input = get_input_keydown(key);
    if (input & PRESS_DOWN) {
        m_menu->advance_pointer(Menu::DirectionDown);
        m_media->play_sound("advance.wav");
    }
    else if (input & PRESS_UP) {
        m_menu->advance_pointer(Menu::DirectionUp);
        m_media->play_sound("advance.wav");
    }
    else if (input & PRESS_ENTER) {
        if (m_menu->get_option() == 4) {
            m_media->play_sound("select.wav");
            return new Area("village.tmx", m_sx, m_sy);
        }
        else {
            m_media->play_sound("reject.wav");
        }
    }
    else if (input & PRESS_ESC) {
        return new Area("village.tmx", m_sx, m_sy);
    }

    return 0;
}

void Shop::draw(SDL_Surface *dest, int x, int y,
                  int clip_x, int clip_y, int clip_w, int clip_h)
{
    Room::draw(dest, x, y, clip_x, clip_y, clip_w, clip_h);
    m_menu->draw(dest, x + 302, y + 40, clip_x, clip_y, clip_w, clip_h);
}

