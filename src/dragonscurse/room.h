#ifndef _Room_H
#define _Room_H

#include "phoboz/media_db.h"

class Area;

class Room {
public:
    Room(const char *image, MediaDB *media, int sx, int sy);
    ~Room();

    virtual Area* move() = 0;
    virtual void draw(SDL_Surface *dest, int x, int y,
                      int clip_x, int clip_y, int clip_w, int clip_h) {
        m_spr->draw(dest, x, y, 0, clip_x, clip_y, clip_w, clip_h);
    }

protected:
    int m_sx;
    int m_sy;

private:
    MediaDB *m_media;
    Sprite *m_spr;
    bool m_loaded;
};

#endif

