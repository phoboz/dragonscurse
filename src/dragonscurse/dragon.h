#ifndef _Dragon_H
#define _Dragon_H

#include "phoboz/timer.h"
#include "player.h"
#include "bullet.h"

class Dragon : public Player {
public:
    Dragon(const char *fn, MediaDB *media, int x, int y, Direction dir);
    virtual bool attack_object(Object *object);
    virtual void move(Map *map);
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    bool m_attack_ready;
    Timer m_attack_timer;
    Bullet *m_bullet;
};

#endif

