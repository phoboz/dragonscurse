#ifndef _Actor_H
#define _Actor_H

#include "phoboz/timer.h"
#include "body.h"

class Status;

class Actor : public Body {
public:
    enum Action {
        Still,
        Move,
        Fall,
        Jump,
        Catapult,
        Crouch,
        Attack,
        AttackLow,
        Hit,
        HitPerish,
        HitPerished
    };

    Actor(Type type, int x, int y, Direction dir)
        : Body(type, x, y, dir),
          m_anim_dir(AnimUp),
          m_action(Still),
          m_invisible(false) { }

    virtual bool set_hit(Object *object = 0, Status *status = 0);
    void reset_hit();
    void set_perish(bool invisible = true);
    Action get_action() const { return m_action; }
    bool get_invisible() const { return m_invisible; }

    virtual bool attack_object(Object *object) { return false; }

    virtual void move(Map *map);
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

protected:
    void set_action(Action action);
    virtual void set_dir(Direction dir = Keep);
    void swap_move_dir();
    void set_attack();
    void reset_attack();
    void animate_move();
    void animate_perish();
    virtual Object::Direction get_reference() const;
    void face_reference(int width = 0);
    void set_invisible(bool invisible);

    AnimDirection m_anim_dir;
    Action m_action;
    bool m_invisible;
    Timer m_anim_timer;
    Timer m_blink_timer;
    Timer m_invisible_timer;
};

#endif

