#ifndef _Player_H
#define _Player_H

#include <list>
#include "phoboz/timer.h"
#include "actor.h"

class Morph;
class Area;
class Item;

class Player : public Actor {
public:
    Player(const char *fn, MediaDB *media, int x, int y, Direction dir);

    void set_jump(Map *map, bool catapult = false);
    virtual bool set_hit(Object *object, Status *status);
    bool check_break_rock(int *x, int *y, Map *map);
    bool check_create_rock(Map *map);

    void set_morph(Morph *morph) { m_morph = morph; }
    bool is_morphing();

    void set_warp(Area *area) { m_area = area; }
    Area* get_warp() const { return m_area; }

    virtual void move(Map *map);
    virtual void draw(Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

protected:
    virtual void set_attack();

private:
    void check_water(Map *map);
    void player_move(Map *map);

    static const int c_rock_timeout = 10;

    Morph *m_morph;
    Area *m_area;
    bool m_hit_ground;
    bool m_jump_ready;
    bool m_in_water;
    Timer m_hit_timer;
    Timer m_break_rock_timer;
    Timer m_create_rock_timer;
};

#endif

