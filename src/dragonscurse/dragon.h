#ifndef _Dragon_H
#define _Dragon_H

#include "player.h"
#include "bullet.h"

class Dragon : public Player {
public:
    Dragon(const char *fn);
    virtual void move(Map *map);
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h) const;

private:
    int m_jump_counter;
    bool m_jump_ready;
    Bullet *m_bullet;
};

#endif

