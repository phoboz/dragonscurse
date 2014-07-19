#ifndef _Arm_H
#define _Arm_H

#include "item.h"

class Arm : public Item  {
public:
    Arm(const char *fn, MediaDB *media, int x, int y)
        : Item(TypeArm, fn, media, x, y) { }
};

#endif

