#ifndef _MainMenu_H
#define _MainMenu_H

#include "phoboz/menu.h"

class MainMenu {
public:
    enum Option {
        OptionNone = -1,
        OptionNew = 0,
        OptionContinue,
        OptionStatus,
        OptionArmList,
        OptionShieldList,
        OptionArmourList,
        OptionQuit
    };

    MainMenu(MediaDB *media);
    ~MainMenu();

    static bool check_menu(int key);

    int get_width() const { return m_menu->get_width(); }

    Option move(int key);

    void draw(SDL_Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    MediaDB *m_media;
    Menu *m_menu;
    static int s_last_option;
};

#endif

