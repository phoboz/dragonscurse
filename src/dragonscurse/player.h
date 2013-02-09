#ifndef _Player_H
#define _Player_H

#include "actor.h"

class Player : public Actor {
public:
    Player(const char *fn)
        : Actor(Object::TypePlayer),
          m_jump_counter(0), m_jump_ready(true) { load(fn); }
    virtual void move(Map *map);

private:
    int m_jump_counter;
    bool m_jump_ready;
};

#endif

