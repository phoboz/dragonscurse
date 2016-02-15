#ifndef _Knight_H
#define _Knight_H

#include "phoboz/timer.h"
#include "player.h"

class Knight : public Player {
public:
    Knight(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Player(fn, media, x, y, dir),
          m_attack_ready(true) { }

    virtual bool attack_object(Object *object);

    virtual bool check_break_rock(int *x, int *y, Map *map);
    virtual bool check_create_rock(Map *map);

    virtual void move(Map *map);

protected:
    bool check_attack(int input);

private:
    static const int c_rock_timeout = 10;

    bool m_attack_ready;
    Timer m_break_rock_timer;
    Timer m_create_rock_timer;
};

#endif

