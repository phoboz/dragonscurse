#ifndef _Hospital_H
#define _Hospital_H

#include <string>
#include "phoboz/menu.h"
#include "world_db.h"
#include "room.h"

class Hospital : public Room {
public:
    Hospital(MediaDB *media, WorldDB *db, const char *src, int sx, int sy);

    virtual Area* move(int key);
    virtual void draw(Surface *dest, int x, int y,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    WorldDB *m_db;
    Sprite *m_spr;
    Text *m_price_label;
    Text *m_price_text;
    Menu *m_menu;
};

#endif

