#ifndef _SubMenu_H
#define _SubMenu_H

#include "phoboz/menu.h"
#include "status.h"

class SubMenu {
public:
    SubMenu(MediaDB *media, Status *status);
    virtual ~SubMenu();

    virtual int move(int key);

    void draw(SDL_Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

protected:
    MediaDB *m_media;
    Status *m_status;
    Menu *m_menu;
};

#endif

