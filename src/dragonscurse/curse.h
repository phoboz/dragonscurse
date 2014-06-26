#ifndef _Curse_H
#define _Curse_H

#include "phoboz/timer.h"
#include "object.h"

class Curse : public Object {
public:
    Curse(const char *fn, int key);

    virtual void move(Map *map);

private:
    int m_world_key;
    AnimDirection m_anim_dir;
    Timer m_anim_timer;
};

#endif

