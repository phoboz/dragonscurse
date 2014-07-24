#include <iostream>
#include "erupter.h"

void Erupter::fire()
{
    bool result = false;

    GravityBullet *bullet = new GravityBullet(get_string("bullet"), m_media);
    if (bullet) {
        if (get_reference() == Right) {
           result = bullet->fire(m_x, m_y,
                                 get_attribute("fire_dx"),
                                 -get_attribute("fire_dy"));
        }
        else {
           result = bullet->fire(m_x, m_y,
                                 -get_attribute("fire_dx"),
                                 -get_attribute("fire_dy"));
        }

        if (result) {
            set_attack();
            m_bullets.push_back(bullet);
        }
    }
}

void Erupter::move(Map *map)
{
    Monster::move(map);

    // Check ground
    check_ground(map);

    if (m_hit == HitOne) {
        if (m_hit_timer.expired(get_attribute("hit_time"))) {
            m_dx = 0;
            reset_hit();
        }
    }

    if (m_attack != AttackNone) {
        if (m_anim_timer.expired(get_attribute("treshold"))) {
            m_attack_timer.reset();
            reset_attack();
        }
    }

    switch(m_action) {
        case Still:
            if (m_hit == HitNone) {
                set_move_dir();
            }
            break;

        case Move:
            if (m_hit == HitNone) {
                if (m_attack_timer.check(get_attribute("attack_timer"))) {
                    m_attack_timer.reset();
                    int dist = get_attribute("attack_distance");
                    int x = m_xref - get_front();
                    int y = m_yref - get_y();
                    if (x * x + y * y < dist * dist) {
                        m_attack_timer.reset();
                        fire();
                    }
                }
            }
            break;

        case Fall:
            check_ahead(map);

            // Move
            if (m_dir == Right) {
                m_x += m_dx;
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
            }

            check_below(map);
            m_y += m_dy;
            break;

        default:
            break;
    }

    // Move bullets
    for (std::list<GravityBullet*>::iterator it = m_bullets.begin();
         it != m_bullets.end();
         ++it) {
        GravityBullet *bullet = (*it);
        bullet->move(map);
    }
}

void Erupter::draw(SDL_Surface *dest, Map *map,
                   int clip_x, int clip_y, int clip_w, int clip_h)
{
    Monster::draw(dest, map, clip_x, clip_y, clip_w, clip_h);

    // Draw bullets
    for (std::list<GravityBullet*>::iterator it = m_bullets.begin();
         it != m_bullets.end();
         ++it) {
        GravityBullet *bullet = (*it);
        bullet->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}

