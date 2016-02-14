#ifndef _Waver_H
#define _Waver_H

#include "phoboz/timer.h"
#include "monster.h"

class Waver : public Monster {
public:
    Waver(const char *fn, MediaDB *media, int x, int y, Direction dir);

    virtual void move(Map *map);

private:
    static const int c_num_steps = 256;
    static bool m_wave_init;
    static int m_wave_y[c_num_steps];

    int m_wave_index;
};

#endif

