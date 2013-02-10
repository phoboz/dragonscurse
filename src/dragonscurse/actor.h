#ifndef _Actor_H
#define _Actor_H

#include "object.h"

class Actor : public Object {
public:
    enum AnimDirection { AnimUp, AnimDown };
    enum Action { Still, Move, Fall, Jump, Crouch, Attack, AttackLow, Ability };

    Actor(Type type, int x, int y, Direction dir)
        : Object(type, x, y, dir),
          m_anim_dir(AnimUp), m_counter(0), m_action(Still) { }

protected:
    bool set_move_dir(Direction dir);
    void swap_move_dir();
    void set_still_instant();
    bool set_still();
    void set_jump();
    void set_crouch();
    void set_attack();
    void reset_attack();
    void animate_move();

    AnimDirection m_anim_dir;
    int m_counter;
    Action m_action;
};

#endif

