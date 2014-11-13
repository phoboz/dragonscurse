#ifndef _Room_H
#define _Room_H

#include <string>
#include "phoboz/media_db.h"
#include "phoboz/text.h"

class Area;

class Room {
public:
    Room(const char *image, const char *font, MediaDB *media,
         const char *src, int sx, int sy, int tx, int ty);
    ~Room();

    virtual Area* move(int key) = 0;
    virtual void draw(Surface *dest, int x, int y,
                      int clip_x, int clip_y, int clip_w, int clip_h);

protected:
    MediaDB *m_media;
    std::string m_src;
    Text *m_text;
    int m_sx;
    int m_sy;

private:
    Sprite *m_spr;
    bool m_loaded;
    int m_tx;
    int m_ty;
};

#endif

