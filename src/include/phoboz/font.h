#ifndef _Font_H
#define _Font_H

#include "SDL_ttf.h"

class Font {
public:
    Font(TTF_Font *f)
        : m_f(f) { }

    TTF_Font* get_ttf() const { return m_f; }

private:
    TTF_Font *m_f;
};

#endif

