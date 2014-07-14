#ifndef _Shop_H
#define _Shop_H

#include "phoboz/menu.h"
#include "room.h"

class Shop : public Room {
public:
    Shop(MediaDB *media, int sx, int sy);

    virtual Area* move(int key);
    virtual void draw(SDL_Surface *dest, int x, int y,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    Menu *m_menu;
};

#endif

