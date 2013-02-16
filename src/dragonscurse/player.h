#ifndef _Player_H
#define _Player_H

#include "phoboz/timer.h"
#include "actor.h"

class Player : public Actor {
public:
    Player(const char *fn, int x, int y, Direction dir)
        : Actor(Object::TypePlayer, x, y, dir),
          m_jump_ready(true) { load(fn); }
    virtual void set_hit(Object *object);
    virtual bool check_collision(Object *object);
    virtual bool attack_actor(Actor *actor) { return false; }
    virtual void move(Map *map);

private:
    bool m_jump_ready;
    Timer m_jump_timer;
    Timer m_hit_timer;
};

#endif

