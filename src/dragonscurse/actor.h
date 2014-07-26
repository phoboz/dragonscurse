#ifndef _Actor_H
#define _Actor_H

#include "phoboz/timer.h"
#include "body.h"

class Actor : public Body {
public:
    enum Action { Still, Move, Fall, Jump, Crouch, MediumAttack, LowAttack };
    enum Hit { HitNone, HitOne, HitPerish, HitPerished };

    Actor(Type type, int x, int y, Direction dir)
        : Body(type, x, y, dir),
          m_anim_dir(AnimUp),
          m_action(Still), m_hit(HitNone),
          m_invisible(false) { }

    virtual bool set_hit(Object *object);
    void reset_hit();
    void set_perish();
    Hit get_hit() const { return m_hit; }
    bool get_invisible() const { return m_invisible; }

    virtual bool attack_actor(Actor *actor) { return false; }

    virtual void move(Map *map);
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

protected:
    // TODO: Remove
    void set_move_dir(Direction dir = Keep) { set_dir(dir); set_action(Move); }

    void set_action(Action action);
    virtual void set_dir(Direction dir = Keep);
    void swap_move_dir();
    void set_attack();
    void reset_attack();
    void check_ground(Map *map);
    void animate_move();
    void face_reference(int width = 0);
    void set_invisible(bool invisible);

    AnimDirection m_anim_dir;
    Action m_action;
    Hit m_hit;
    bool m_invisible;
    Timer m_anim_timer;
    Timer m_blink_timer;
    Timer m_invisible_timer;
};

#endif

