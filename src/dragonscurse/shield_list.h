#ifndef _ShieldList_H
#define _ShieldList_H

#include "phoboz/menu.h"
#include "status.h"

class ShieldList {
public:
    ShieldList(MediaDB *media, Status *status);

    int move(int key);

    void draw(SDL_Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    static const int c_max_entries = 40;

    MediaDB *m_media;
    Status *m_status;
    Menu *m_menu;
};

#endif

