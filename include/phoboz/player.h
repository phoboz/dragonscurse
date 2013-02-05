#ifndef _Player_H
#define _Player_H

#include "phoboz/object.h"

class Player : public Object {
public:
    Player(const char *fn)
        : Object(Object::Player),
          m_jump_counter(0), m_jump_ready(true) { load(fn); }
    virtual void move(Map *map);

private:
    int m_jump_counter;
    bool m_jump_ready;
};

#endif

