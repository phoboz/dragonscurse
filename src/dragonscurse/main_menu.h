#ifndef _MainMenu_H
#define _MainMenu_H

#include "phoboz/menu.h"
#include "status.h"

class MainMenu {
public:
    MainMenu(MediaDB *media, Status *status);

    static bool check_menu(int key);

    bool move(int key);

    void draw(SDL_Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    MediaDB *m_media;
    Status *m_status;
    Menu *m_menu;
};

#endif

