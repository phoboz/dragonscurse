#ifndef _Room_H
#define _Room_H

#include "phoboz/media_db.h"
#include "phoboz/text.h"

class Area;

class Room {
public:
    Room(const char *image, const char *font, MediaDB *media, int sx, int sy,
         int tx, int ty);
    ~Room();

    virtual Area* move() = 0;
    virtual void draw(SDL_Surface *dest, int x, int y,
                      int clip_x, int clip_y, int clip_w, int clip_h);

protected:
    Text *m_text;
    int m_sx;
    int m_sy;

private:
    MediaDB *m_media;
    Sprite *m_spr;
    bool m_loaded;
    int m_tx;
    int m_ty;
};

#endif

