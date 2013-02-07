#ifndef _Actor_H
#define _Actor_H

#include "phoboz/object.h"

class Actor : public Object {
public:
    enum AnimDirection { AnimUp, AnimDown };
    enum Action { Still, Move, Fall, Jump, Crouch, Attack, Ability };

    Actor(Type type)
        : Object(type),
          m_anim_dir(AnimUp), m_counter(0), m_action(Still) { }

protected:
    bool set_move_dir(Direction dir);
    bool set_still();
    void set_jump();
    void set_crouch();
    void set_attack();
    void animate_move();

    AnimDirection m_anim_dir;
    int m_counter;
    Action m_action;
};

#endif

