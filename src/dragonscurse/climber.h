#ifndef _Climber_H
#define _Climber_H

#include "knight.h"

class Climber : public Knight {
public:
    enum ClimbDir { ClimbNone, ClimbAbove, ClimbBelow, ClimbLeft, ClimbRight };

    Climber(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Knight(fn, media, x, y, dir),
          m_climb_dir(ClimbNone),
          m_leave_ready(false) { }

    virtual void set_dir(Direction dir);

    virtual void move(Map *map);

private:
    void set_climb_above(Direction set_dir);
    void set_climb_below(Direction set_dir);
    void set_climb_right(Direction set_dir);
    void set_climb_left(Direction set_dir);

    void animate_climb_above();
    void animate_climb_below();
    void animate_climb_right();
    void animate_climb_left();
    void animate_climb();

    bool animate_attack_above();
    bool animate_attack_below();
    bool animate_attack_right();
    bool animate_attack_left();
    virtual bool animate_attack();

    void enter_climb(Map *map, ClimbDir dir, int x, int y);
    void leave_climb(Map *map);

    int check_climb(Map *map, int len = 1, Direction dir = Keep);
    bool climb_above_turn_down(Map *map);
    bool climb_below_turn_up(Map *map);
    bool climb_right_turn_right(Map *map);
    bool climb_right_turn_left(Map *map);
    bool climb_left_turn_left(Map *map);

    void move_climb(Map *map, int input);

    static const int c_leave_time = 32;

    ClimbDir m_climb_dir;
    Timer m_leave_timer;
    bool m_leave_ready;
};

#endif

