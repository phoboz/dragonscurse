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
    virtual void move(Map *map);

protected:
    bool check_attack(int input);

private:
    bool m_attack_ready;
};

#endif

