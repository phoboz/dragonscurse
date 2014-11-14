#ifndef _Font_H
#define _Font_H

#include "phoboz/surface.h"
#include "SDL_ttf.h"

class Font {
public:
    Font(TTF_Font *f)
        : m_f(f),
          m_loaded(true) { }

    Font(const char *fn, int size) { load(fn, size); }

    static bool init();
    bool load(const char *fn, int size);

    Surface* get_surface(const char *str, Color *color) const;
    void get_dimensions(int *w, int *h, const char *str);
    int get_line_skip() const { return TTF_FontLineSkip(m_f); }

private:
    static bool m_initialized;
    bool m_loaded;
    TTF_Font *m_f;
};

#endif

