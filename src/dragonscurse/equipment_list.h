#ifndef _EquipmentList_H
#define _EquipmentList_H

#include "sub_menu.h"
#include "status.h"
#include "item.h"

class EquipmentList : public SubMenu {
public:
    EquipmentList(MediaDB *media, Status *status,
                  Item::ItemType item_type, int spr_index);
    virtual ~EquipmentList();

    virtual int move(int key);

private:
    Status *m_status;
    Sprite *m_spr;
    int m_spr_index;
    int m_curr_eq;
};

#endif

