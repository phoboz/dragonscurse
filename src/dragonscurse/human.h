#ifndef _Human_H
#define _Human_H

#include "phoboz/timer.h"
#include "knight.h"

class Human : public Knight {
public:
    Human(const char *fn, int x, int y, Direction dir)
        : Knight(fn, x, y, dir) { }
};

#endif

