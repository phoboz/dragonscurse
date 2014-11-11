#ifndef _Church_H
#define _Church_H

#include "phoboz/menu.h"
#include "world_db.h"
#include "room.h"

class Church : public Room {
public:
    Church(MediaDB *media, WorldDB *db, const char *src, int sx, int sy);

    virtual Area* move(int key);
    virtual void draw(SDL_Surface *dest, int x, int y,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    Menu *m_menu;
    WorldDB *m_db;
};

#endif

