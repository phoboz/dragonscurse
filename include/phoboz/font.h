#ifndef _Font_H
#define _Font_H

#include "phoboz/media_db.h"

class Font {
public:
    Font(const char *fn, MediaDB *media);
    ~Font();

    bool get_loaded() { return m_spr->get_loaded(); }

    void draw(SDL_Surface *dest, int x, int y, const char *msg,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    MediaDB *m_media;
    Sprite *m_spr;
};

#endif

