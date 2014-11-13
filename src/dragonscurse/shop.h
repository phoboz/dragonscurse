#ifndef _Shop_H
#define _Shop_H

#include <string>
#include "phoboz/menu.h"
#include "world_db.h"
#include "room.h"

class Shop : public Room {
public:
    Shop(const char *name, MediaDB *media, WorldDB *db,
         const char *src, int sx, int sy);

    virtual Area* move(int key);
    virtual void draw(Surface *dest, int x, int y,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    std::string m_name;
    WorldDB *m_db;
    Text *m_price_label;
    Text *m_price_text;
    Menu *m_menu;
};

#endif

