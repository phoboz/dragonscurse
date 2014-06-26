#ifndef _Curse_H
#define _Curse_H

#include <string>
#include "phoboz/timer.h"
#include "object.h"

struct ObjectInfo;

class Curse : public Object {
public:
    Curse(ObjectInfo *info);

    virtual void move(Map *map);

private:
    int m_world_key;
    std::string m_player;
    std::string m_destination;
    int m_start_x, m_start_y;
    AnimDirection m_anim_dir;
    Timer m_anim_timer;
};

#endif

