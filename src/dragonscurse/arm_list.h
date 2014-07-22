#ifndef _ArmList_H
#define _ArmList_H

#include "equipment_list.h"

class ArmList : public EquipmentList {
public:
    ArmList(MediaDB *media, Status *status)
        : EquipmentList(media, status, Item::TypeArm, 0) { }
};

#endif

