#ifndef _Morph_H
#define _Morph_H

#include "phoboz/timer.h"
#include "object.h"

class Morph : public Object {
public:
    Morph(const char *fn, int x, int y, Object::Direction dir);

    bool is_done() const { return m_done; }

    virtual void move(Map *map);

private:
    bool m_done;
    Timer m_anim_timer;
};

#endif

