#ifndef _SubMenu_H
#define _SubMenu_H

#include "phoboz/menu.h"

class SubMenu {
public:
    enum Type { TypeEquipment, TypeItem, TypeSave };

    SubMenu(Type type, MediaDB *media);
    virtual ~SubMenu();

    int get_width() const { return m_menu->get_width(); }
    Type get_type() const { return m_type; }

    virtual int move(int key);

    void draw(SDL_Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

protected:
    MediaDB *m_media;
    Menu *m_menu;
    Type m_type;
};

#endif

