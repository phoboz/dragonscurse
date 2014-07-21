#include "phoboz/ctrl.h"
#include "shield_list.h"

ShieldList::ShieldList(MediaDB *media, Status *status)
    : m_media(media),
      m_status(status)
{
    m_menu = new Menu("Wonderfull_12", "icons.png", 0, media);
    m_menu->add_option("Back");

    static char *str_list[c_max_entries];
    for (int i = 0; i < c_max_entries; i++) {
        str_list[i] = new char[80];
    }

    int n = status->shield_list(str_list, c_max_entries);

    for (int i = 0; i < n; i++) {
        m_menu->add_option(str_list[i]);
    }

    for (int i = 0; i < c_max_entries; i++) {
        delete str_list[i];
    }
}

int ShieldList::move(int key)
{
    int result;
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
        m_media->play_sound("select.wav");
        result = m_menu->get_option();
    }
    else if (input & PRESS_ESC) {
        result = -1;
    }

    return result;
}

void ShieldList::draw(SDL_Surface *dest, int x, int y,
                      int clip_x, int clip_y, int clip_w, int clip_h)
{
    m_menu->draw(dest, x, y, clip_x, clip_y, clip_w, clip_h);
}

