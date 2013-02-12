#ifndef _Human_H
#define _Human_H

#include "player.h"

class Human : public Player {
public:
    Human(const char *fn, int x, int y, Direction dir)
        : Player(fn, x, y, dir),
          m_attack_ready(true) { }
    virtual void move(Map *map);

private:
    bool m_attack_ready;
    int m_attack_counter;
};

#endif

