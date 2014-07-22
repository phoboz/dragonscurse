#ifndef _ShieldList_H
#define _ShieldList_H

#include "sub_menu.h"

class ShieldList : public SubMenu {
public:
    ShieldList(MediaDB *media, Status *status);
    virtual ~ShieldList();

    virtual int move(int key);

private:
    Sprite *m_spr;
    int m_curr_eq;
};

#endif

