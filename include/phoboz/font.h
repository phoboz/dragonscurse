#ifndef _Font_H
#define _Font_H

#include "phoboz/sprite.h"

class Font {
public:
    Font(const char *fn, int w, int h, int margin, int spacing);
    ~Font();

    bool get_loaded() { return m_spr->get_loaded(); }

    void draw(SDL_Surface *dest, int x, int y, const char *msg,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    Sprite *m_spr;
};

#endif

