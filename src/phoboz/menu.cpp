#include <stdio.h>
#include "phoboz/menu.h"

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

void Menu::draw(SDL_Surface *dest, int x, int y,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    int height = 0;

    for (int i = 0; i < m_options.size(); i++) {
        Text *text = m_options[i];
        text->draw(dest, x, y + height, clip_x, clip_y, clip_w, clip_h);
        height += text->get_height();
    }
}

