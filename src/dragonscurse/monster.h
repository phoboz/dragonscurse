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

    bool get_hit_ground() const { return m_hit_ground; }
    void set_invinsible(bool value) { m_invinsible = value; }
    void set_jump(Map *map);
    virtual bool set_hit(Object *object, Status *status);

    Object* release_object();

    virtual void move(Map *map);

protected:
    void set_recursive_hit(bool recursive_hit) {
        m_recursive_hit = recursive_hit;
    }

    void process_hit();

private:
    int m_curr_hp;
    bool m_invinsible;
    bool m_hit_ground;
    bool m_recursive_hit;
    Timer m_hit_timer;
    Timer m_perish_timer;
    std::list<Object*> m_objects;
};

#endif

