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

void Text::draw(SDL_Surface *dest, int x, int y)
{
    SDL_Color color = {255, 255, 255};
    SDL_Rect rect;

    rect.x = x;

    for (int i = 0; i < m_lines.size(); i++) {
        TextLine *line = m_lines[i];

        rect.y = y + line->m_y;
        SDL_Surface *surf = TTF_RenderText_Solid(m_font,
                                                 line->m_text.c_str(),
                                                 color);
        SDL_BlitSurface(surf, NULL, dest, &rect);
        SDL_FreeSurface(surf);
    }
}

