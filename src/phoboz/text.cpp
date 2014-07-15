#include <string>
#include <sstream>
#include "phoboz/text.h"

struct TextLine {
    TextLine(const char *str, int y)
        : m_text(str), 
          m_y(y) {
        m_text = std::string(str);
    }

    int m_y;
    std::string m_text;
};

bool Text::m_initialized = false;

Text::Text(const char *fontname, MediaDB *media,
           const Sprite *icon_spr, int icon_index)
    : m_media(media),
      m_icon_index(icon_index)
{
    m_font = media->get_font(fontname);
    if (icon_spr) {
        media->reference_sprite(icon_spr);
        m_icon_spr = (Sprite *) icon_spr;
    }
    else {
        m_icon_spr = 0;
    }
}

Text::~Text()
{
    for (int i = 0; i < m_lines.size(); i++) {
        delete m_lines[i];
    }

    if (m_icon_spr) {
        m_media->leave_sprite(m_icon_spr);
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
    TextLine *line = new TextLine(str,
                                  m_lines.size() * TTF_FontLineSkip(m_font));

    return line;
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

bool Text::add_text(const char *str)
{
    bool result = true;
    std::istringstream ss(str);
    std::string line;

    while (std::getline(ss, line)) {
        if (!add_line(line.c_str())) {
            result = false;
            break;
        }
    }

    return result;
}

int Text::get_height() const
{
    return m_lines.size() * TTF_FontLineSkip(m_font);
}

void Text::draw(SDL_Surface *dest, int x, int y,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    SDL_Color color = {255, 255, 255};
    SDL_Rect rect;
    SDL_Rect clip;

    if (m_icon_spr) {
        int w = m_icon_spr->get_width();
        rect.x = x + w + w / 2;
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

