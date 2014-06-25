#ifndef _Monster_H
#define _Monster_H

#include "phoboz/timer.h"
#include "actor.h"

class Item;
class World;

class Monster : public Actor {
public:
    Monster(const char *fn, int x, int y, Direction dir);

    virtual void world_initialize(World *world);

    void set_invinsible(bool value) { m_invinsible = value; }
    virtual bool set_hit(Object *object);

    Item* get_item() { return m_item; }

    virtual void move(Map *map);

private:
    int m_curr_hp;
    bool m_invinsible;
    Timer m_perish_timer;
    Item *m_item;
};

#endif

