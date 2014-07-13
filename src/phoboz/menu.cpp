#include <stdio.h>
#include "phoboz/menu.h"

Menu::Menu(const char *fontname,
           const char *pointer, int pointer_index,
           MediaDB *media)
    : m_fontname(fontname),
      m_media(media),
      m_pointer_index(pointer_index),
      m_curr_option(0)
{
    m_pointer_spr = media->get_sprite(pointer);
}

bool Menu::add_option(const char *str, const char *icon, int icon_index)
{
    bool result = false;

    Text *text = new Text(m_fontname.c_str(), m_media, icon, icon_index);
    if (text) {
        text->add_text(str);
        m_options.push_back(text);
        result = true;
    }

    return result;
}

void Menu::advance_pointer(PointerDirection dir)
{
    if (dir == DirectionUp) {
        if (--m_curr_option < 0) {
            m_curr_option = m_options.size() - 1;
        }
        m_media->play_sound("advance.wav");
    }
    else if (dir == DirectionDown) {
        if (++m_curr_option == m_options.size()) {
            m_curr_option = 0;
        }
        m_media->play_sound("advance.wav");
    }
}

void Menu::draw(SDL_Surface *dest, int x, int y,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    int height = 0;

    for (int i = 0; i < m_options.size(); i++) {
        Text *text = m_options[i];
        text->draw(dest, x + m_pointer_spr->get_width(), y + height,
                   clip_x, clip_y, clip_w, clip_h);
        if (i == m_curr_option) {
            m_pointer_spr->draw(dest, x, y + height, m_pointer_index,
                                clip_x, clip_y, clip_w, clip_h);
        }
        height += text->get_height();
    }
}

