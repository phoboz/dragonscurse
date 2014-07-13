#include <string>
#include "phoboz/text.h"

struct TextLine {
    TextLine(const char *str, int y)
        : m_y(y) {
        m_text = std::string(str);
    }

    int m_y;
    std::string m_text;
};

bool Text::m_initialized = false;

Text::Text(const char *fontname, MediaDB *media,
           const char *icon, int icon_index)
    : m_media(media),
      m_curr_line(0),
      m_icon_index(icon_index)
{
    m_font = media->get_font(fontname);
    if (icon) {
        set_icon(icon, icon_index);
    }
}

Text::~Text()
{
    for (int i = 0; i < m_lines.size(); i++) {
        delete m_lines[i];
    }
}

bool Text::init()
{
    bool result = false;

    if (m_initialized) {
        result = true;
    }
    else {
        if(TTF_Init() != -1) {
            result = true;
        }
    }

    return result;
}

TTF_Font* Text::load_font(const char *fn, int size)
{
    return TTF_OpenFont("wonderfull.ttf", size);
}

TextLine* Text::new_line(const char *str)
{
    TextLine *line = new TextLine(str, m_curr_line * TTF_FontLineSkip(m_font));
    m_curr_line++;

    return line;
}

bool Text::set_icon(const char *icon, int icon_index)
{
    m_icon_spr = m_media->get_sprite(icon);
    m_icon_index = icon_index;
}

bool Text::add_line(const char *str)
{
    bool result = false;
    TextLine *line = new_line(str);
    if (line) {
        m_lines.push_back(line);
        result = true;
    }

    return result;
}

void Text::draw(SDL_Surface *dest, int x, int y,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    SDL_Color color = {255, 255, 255};
    SDL_Rect rect;
    SDL_Rect clip;

    if (m_icon_spr) {
        rect.x = x + m_icon_spr->get_width();
    }
    else {
        rect.x = x;
    }

    clip.x = clip_x;
    clip.y = clip_y;
    clip.w = clip_w;
    clip.h = clip_h;

    for (int i = 0; i < m_lines.size(); i++) {
        TextLine *line = m_lines[i];

        rect.y = y + line->m_y;
        SDL_Surface *surf =
            TTF_RenderText_Solid(m_font, line->m_text.c_str(), color);
        SDL_BlitSurface(surf, &clip, dest, &rect);
        SDL_FreeSurface(surf);
    }

    if (m_icon_spr) {
        m_icon_spr->draw(dest, x, y, m_icon_index,
                         clip_x, clip_y, clip_w, clip_h);
    }
}

