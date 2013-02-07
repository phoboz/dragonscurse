#include <iostream>
#include <string.h>
#include "phoboz/ctrl.h"
#include "phoboz/dragon.h"

Dragon::Dragon(const char *fn)
        : Player(fn),
          m_jump_counter(0), m_jump_ready(true)
{
    m_bullet = new Bullet(get_string("bullet"));
    if (!m_bullet->get_loaded()) exit(1);
}

void Dragon::move(Map *map)
{
    Player::move(map);

    int input = get_input();

    // TODO: Check in which state it shall be possible to fire
    if (input & PRESS_ATTACK) {
        int y;
        if (m_action == Crouch) {
            y = get_attribute("attack_low");
        }
        else {
            y = get_attribute("attack_high");
        }

        if (m_dir == Right) {
            if (m_bullet->fire(m_x + get_attribute("right"),
                               m_y + get_attribute("top") + y,
                               m_dir)) {
                set_attack();
            }
        }
        else {
            if (m_bullet->fire(m_x + get_attribute("left"),
                               m_y + get_attribute("top") + y,
                               m_dir)) {
                set_attack();
            }
        }
    }
    else if (m_action == Attack) {
        set_still();
    }

    // Move bullet
    m_bullet->move(map);
}

void Dragon::draw(SDL_Surface *dest, Map *map,
                  int clip_x, int clip_y, int clip_w, int clip_h) const
{
    Object::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    m_bullet->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
}

