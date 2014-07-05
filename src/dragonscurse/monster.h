#ifndef _Monster_H
#define _Monster_H

#include <list>
#include "phoboz/timer.h"
#include "actor.h"

class World;

class Monster : public Actor {
public:
    Monster(const char *fn, MediaDB *media, int x, int y, Direction dir);

    virtual void world_initialize(World *world);

    void set_invinsible(bool value) { m_invinsible = value; }
    virtual bool set_hit(Object *object);

    Object* release_object();

    virtual void move(Map *map);

private:
    int m_curr_hp;
    bool m_invinsible;
    Timer m_perish_timer;
    std::list<Object*> m_objects;
};

#endif

