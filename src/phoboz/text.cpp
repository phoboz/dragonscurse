#include <string.h>
#include <string>
#include <sstream>
#include "SDL_ttf.h"
#include "phoboz/text.h"

struct TextLine {
    TextLine(const char *str, int y, Font *font, Color &color)
        : m_y(y),
          m_font(font),
          m_color(color) {
        set_text(str, &color);
    }

    ~TextLine() {
        delete m_surface;
    }

    bool replace_text(const char *str) {
        delete m_surface;
        return set_text(str, &m_color);
    }

    bool set_text(const char *str, Color *color) {
        bool result = false;

        m_surface = new Surface(TTF_RenderText_Solid(m_font->get_ttf(),
                                str, *color));
        if (m_surface) {
            TTF_SizeText(m_font->get_ttf(), str, &m_w, &m_h);
            result = true;
        }

        return result;
    }

    int m_y;
    int m_w, m_h;
    Font *m_font;
    Color m_color;
    Surface *m_surface;
};

bool Text::m_initialized = false;

Text::Text(const char *fontname, MediaDB *media, void *data,
           const Sprite *icon_spr, int icon_index)
    : m_media(media),
      m_color(Color::White),
      m_data(data)
{
    m_font = media->get_font(fontname);
    set_icon(icon_spr, icon_index);
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

Font* Text::load_font(const char *fn, int size)
{
    return new Font(TTF_OpenFont(fn, size));
}

void Text::set_icon(const Sprite *icon_spr, int icon_index)
{
    if (icon_spr) {
        m_media->reference_sprite(icon_spr);
    }

    m_icon_spr = (Sprite *) icon_spr;
    m_icon_index = icon_index;
}

TextLine* Text::new_line(const char *str)
{
    TTF_Font *f = m_font->get_ttf();
    TextLine *line = new TextLine(str, m_lines.size() * TTF_FontLineSkip(f),
                                  m_font, m_color);

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

bool Text::replace_line(const char *str, int line_no)
{
    return m_lines[line_no]->replace_text(str);
}

bool Text::replace_line(const char *str, Color &color, int line_no)
{
    m_lines[line_no]->m_color = color;
    return m_lines[line_no]->replace_text(str);
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

int Text::get_width() const
{
    int result = 0;

    for (int i = 0; i < m_lines.size(); i++) {
        int w = m_lines[i]->m_w;
        if (w > result) {
            result = w;
        }
    }

    return result;
}

int Text::get_height() const
{
    return m_lines.size() * TTF_FontLineSkip(m_font->get_ttf());
}

void Text::draw(Surface *dest, int x, int y,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    int rect_x;

    if (m_icon_spr) {
        int w = m_icon_spr->get_width();
        rect_x = x + w + w / 2;
    }
    else {
        rect_x = x;
    }

    Rect clip(clip_x, clip_y, clip_w, clip_h);

    for (int i = 0; i < m_lines.size(); i++) {
        TextLine *line = m_lines[i];

        Rect rect(rect_x, y + line->m_y, 0, 0);
        line->m_surface->draw(&clip, dest, &rect);
    }

    if (m_icon_spr) {
        m_icon_spr->draw(dest, x, y, m_icon_index,
                         clip_x, clip_y, clip_w, clip_h);
    }
}

