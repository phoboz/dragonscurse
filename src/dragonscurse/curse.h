#ifndef _Curse_H
#define _Curse_H

#include <string>
#include "phoboz/timer.h"
#include "object.h"

struct ObjectInfo;

class Curse : public Object {
public:
    Curse(ObjectInfo *info, MediaDB *media);

    const char* get_destination() { return m_destination.c_str(); }
    const char* get_player() { return m_player.c_str(); }
    int get_sx() { return m_sx; }
    int get_sy() { return m_sy; }

    virtual void move(Map *map);

private:
    int m_world_key;
    std::string m_player;
    std::string m_destination;
    int m_sx, m_sy;
    AnimDirection m_anim_dir;
    Timer m_anim_timer;
};

#endif

