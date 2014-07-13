#ifndef _Church_H
#define _Church_H

#include "phoboz/menu.h"
#include "room.h"

class Church : public Room {
public:
    Church(const char *image, MediaDB *media, int sx, int sy);

    virtual Area* move();
    virtual void draw(SDL_Surface *dest, int x, int y,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    Menu *m_menu;
};

#endif

