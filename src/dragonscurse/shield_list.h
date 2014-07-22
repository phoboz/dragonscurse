#ifndef _ShieldList_H
#define _ShieldList_H

#include "equipment_list.h"

class ShieldList : public EquipmentList {
public:
    ShieldList(MediaDB *media, Status *status)
        : EquipmentList(media, status, Item::TypeShield, 1) { }
};

#endif

