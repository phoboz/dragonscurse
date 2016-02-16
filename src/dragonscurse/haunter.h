#ifndef _Haunter_H
#define _Haunter_H

#include "monster.h"

class Haunter : public Monster {
public:
    Haunter(const char *fn, MediaDB *media, int x, int y, int w, int h,
            Direction dir);

    virtual void move(Map *map);

private:
    static const int c_num_steps = 256;
    static bool m_circle_init;
    static int m_circle_x[c_num_steps];
    static int m_circle_y[c_num_steps];

    int m_circle_index;
    int m_w, m_h;
    int m_center_x;
    int m_center_y;
};

#endif

