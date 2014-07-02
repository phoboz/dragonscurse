#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phoboz/font.h"

Font::Font(const char *fn, int w, int h, int margin, int spacing)
{
    m_spr = new Sprite(fn, w, h, margin, spacing);
}

Font::~Font()
{
    delete m_spr;
}

void Font::draw(SDL_Surface *dest, int x, int y, const char *msg,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    int i, len;
    int dx, dy, w;

    // Cache properties
    len = strlen(msg);
    dx = x;
    dy = y;
    w = m_spr->get_width();

    // Draw a sprite for each character
    for (i = 0; i < len; i++) {
        m_spr->draw(dest, dx, dy, msg[i] - ' ',
                    clip_x, clip_y, clip_w, clip_h);
        dx += w;
    }
}

