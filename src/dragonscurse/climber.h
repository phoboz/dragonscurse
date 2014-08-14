#ifndef _Climber_H
#define _Climber_H

#include "knight.h"

class Climber : public Knight {
public:
    enum ClimbDir { ClimbNone, ClimbUp, ClimbDown, ClimbLeft, ClimbRight };

    Climber(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Knight(fn, media, x, y, dir),
          m_climb_dir(ClimbNone) { }

    virtual void set_dir(Direction dir = Keep);

    virtual void move(Map *map);

private:
    void set_climb_right(Direction set_dir);
    void set_climb_left(Direction set_dir);

    void animate_climb_right();
    void animate_climb_left();
    void animate_climb();

    void move_climb(Map *map);

    ClimbDir m_climb_dir;
};

#endif

