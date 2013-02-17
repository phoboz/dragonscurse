#ifndef _Actor_H
#define _Actor_H

#include "phoboz/timer.h"
#include "object.h"

class Actor : public Object {
public:
    enum AnimDirection { AnimUp, AnimDown };
    enum Action { Still,
                  Move,
                  Fall,
                  Jump,
                  Crouch,
                  Hit,
                  Ability };
    enum Attack { AttackNone, AttackMedium, AttackLow };

    Actor(Type type, int x, int y, Direction dir)
        : Object(type, x, y, dir),
          m_anim_dir(AnimUp), m_action(Still), m_attack(AttackNone),
          m_xref(0), m_yref(0),
          m_invisible(false) { }
    void set_reference(int x, int y) { m_xref = x; m_yref = y; }
    virtual void set_hit(Object *object);
    virtual void move(Map *map);
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

protected:
    bool set_move_dir(Direction dir);
    void swap_move_dir();
    void set_still();
    void set_fall();
    void set_jump_dir(Direction dir);
    void set_crouch();
    void set_attack();
    void reset_attack();
    void check_ground(Map *map);
    void animate_move();
    void face_reference();
    void set_invisible(bool invisible);
    bool get_invisible() const { return m_invisible; }

    AnimDirection m_anim_dir;
    Action m_action;
    Attack m_attack;
    int m_xref, m_yref;
    bool m_invisible;
    Timer m_anim_timer;
    Timer m_blink_timer;
    Timer m_invisible_timer;
};

#endif

