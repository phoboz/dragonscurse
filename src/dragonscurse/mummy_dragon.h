#ifndef _MummyDragon_H
#define _MummyDragon_H

#include <vector>
#include "phoboz/timer.h"
#include "monster.h"
#include "vector_bullet.h"

class MummyDragon : public Monster {
public:
    MummyDragon(const char *fn, MediaDB *media, int x, int y, Direction dir);

    virtual bool attack_object(Object *object);

    virtual bool get_visible(Map *map, int clip_x, int clip_y,
                             int clip_w, int clip_h) const;
    virtual void move(Map *map);
    virtual void draw(Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    void fire();

    int m_left, m_right;
    int m_top, m_bottom;
    bool m_is_flying;
    int m_fly_time;
    int m_fly_speed;
    int m_bullet_index;
    std::vector<VectorBullet*> m_bullets;
    Timer m_attack_timer;
    Timer m_fire_timer;
    Timer m_turn_counter;
    Timer m_fly_timer;
};

#endif

