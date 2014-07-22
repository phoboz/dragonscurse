#ifndef _ArmourList_H
#define _ArmourList_H

#include "equipment_list.h"

class ArmourList : public EquipmentList {
public:
    ArmourList(MediaDB *media, Status *status)
        : EquipmentList(media, status, Item::TypeArmour, 2) { }
};

#endif

