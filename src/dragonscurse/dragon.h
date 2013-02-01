#ifndef _Dragon_H
#define _Dragon_H

#include "object.h"

class Dragon : public Object {
public:
    Dragon(const char *fn)
        : Object(Object::Player),
          m_jump_counter(0), m_jump_ready(true) { load(fn); }
    virtual void move(Map *map);

private:
    int m_jump_counter;
    bool m_jump_ready;
};

#endif

