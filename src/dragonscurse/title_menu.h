#ifndef _TitleMenu_H
#define _TitleMenu_H

#include "phoboz/menu.h"

class TitleMenu {
public:
    enum Option {
        OptionNone = -1,
        OptionNew = 0,
        OptionLoad,
        OptionQuit
    };

    TitleMenu(MediaDB *media);
    ~TitleMenu();

    int get_width() const { return m_menu->get_width(); }

    Option move(int key);

    void draw(Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    MediaDB *m_media;
    Menu *m_menu;
    static int s_last_option;
};

#endif

