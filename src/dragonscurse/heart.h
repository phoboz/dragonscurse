#ifndef _Heart_H
#define _Heart_H

#include "phoboz/media_db.h"
#include "phoboz/sprite.h"

class Heart {
public:
    Heart(MediaDB *media);

    void set_content_percent(int percent) { m_percent = percent; }

    int get_width() { return m_spr->get_width(); }

    void draw(SDL_Surface *surface, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    MediaDB *m_media;
    bool m_loaded;
    Sprite *m_spr;
    int m_percent;
};

#endif

