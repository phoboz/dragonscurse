#ifndef _Surface_H
#define _Surface_H

#include "rect.h"
#include "color.h"

class Surface {
public:
    Surface(SDL_Surface *s)
        : m_s(s),
          m_initialized(true) { }

    Surface(const char *fn) { load(fn); }

    ~Surface();

    bool load(const char *fn);

    bool get_initialized() const { return m_initialized; }
    int get_width() const { return m_s->w; }
    int get_height() const { return m_s->h; }
    SDL_PixelFormat* get_format() const { return m_s->format; }
    void get_pixel(Color *c, int x, int y);

    void fill_rect(Rect *rect, Color *c);
    void draw(Rect *src_rect, Surface *dest, Rect *dest_rect);
    void flip() { SDL_Flip(m_s); }

private:
    bool m_initialized;
    SDL_Surface *m_s;
};

#endif

