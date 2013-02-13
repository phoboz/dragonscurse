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
                  Attack, AttackLow,
                  Hit,
                  Ability };

    Actor(Type type, int x, int y, Direction dir)
        : Object(type, x, y, dir),
          m_anim_dir(AnimUp), m_action(Still),
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
    void set_still_instant();
    bool set_still();
    void set_jump();
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
    int m_xref, m_yref;
    bool m_invisible;
    Timer m_anim_timer;
    Timer m_blink_timer;
    Timer m_invisible_timer;
};

#endif

