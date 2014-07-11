#ifndef _Text_H
#define _Text_H

#include <vector>
#include "SDL_ttf.h"
#include "phoboz/media_db.h"

// Hidden
struct TextLine;

class Text {
public:
    Text(TTF_Font *font)
        : m_font(font),
          m_curr_line(0) { }
    Text(const char *fontname, MediaDB *media);

    ~Text();

    static bool init();
    static TTF_Font* load_font(const char *fn, int size);

    bool add_line(const char *str);

    void draw(SDL_Surface *dest, int x, int y);

private:
    TextLine* new_line(const char *str);

    static bool m_initialized;
    TTF_Font *m_font;
    int m_curr_line;
    std::vector<TextLine*> m_lines;
};

#endif

