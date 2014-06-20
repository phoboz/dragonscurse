#ifndef _MekaDragon_H
#define _MekaDragon_H

#include <vector>
#include "phoboz/timer.h"
#include "monster.h"
#include "bullet.h"

class MekaDragon : public Monster {
public:
    MekaDragon(const char *fn, int x, int y, Direction dir);
    virtual void move(Map *map);
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    HorizontalDirection m_horizontal_dir;
    int m_bullet_index;
    std::vector<Bullet*> m_bullets;
    Timer m_attack_timer;
    Timer m_idle_timer;
    Timer m_fire_timer;
    Timer m_hit_timer;
};

#endif
