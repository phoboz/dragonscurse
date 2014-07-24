#ifndef _ItemList_H
#define _ItemList_H

#include "sub_menu.h"
#include "item.h"

class ItemList : public SubMenu {
public:
    ItemList(MediaDB *media, Status *status, Item::ItemType item_type);
    virtual ~ItemList();

    virtual int move(int key);

private:
    Sprite *m_spr;
    int m_spr_index;
};

#endif

