#ifndef _Surface_H
#define _Surface_H

#include "rect.h"
#include "color.h"

class Surface {
public:
    Surface(SDL_Surface *s)
        : m_s(s) { }

    ~Surface() { SDL_FreeSurface(m_s); }

    int get_width() const { return m_s->w; }
    int get_height() const { return m_s->h; }
    SDL_PixelFormat* get_format() const { return m_s->format; }
    void get_pixel(Color *c, int x, int y);

    void fill_rect(Rect *rect, Color *c);
    void draw(Rect *src_rect, Surface *dest, Rect *dest_rect);
    void flip() { SDL_Flip(m_s); }

private:
    SDL_Surface *m_s;
};

#endif

