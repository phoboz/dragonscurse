#include <stdlib.h>
#include "crawler.h"

Crawler::Crawler(const char *fn, MediaDB *media, int x, int y, Direction dir)
    : Monster(fn, media, x, y, dir),
      m_jump_counter(0)
{
    const char* bullet_name = get_string("bullet");
    int num_bullets = get_attribute("num_bullets");

    for (int i = 0; i < num_bullets; i++) {
        VectorBullet *bullet = new VectorBullet(bullet_name, media);
        if (!bullet->get_loaded()) {
            exit(1);
        }
        m_bullets.push_back(bullet);
    }
}

bool Crawler::attack_object(Object *object)
{
    bool result = false;
    unsigned n = m_bullets.size();

    for (int i = 0; i < n; i++) {
        if (m_bullets[i]->hit_object(object)) {
            result = true;
            break;
        }
    }

    return result;
}

void Crawler::check_ground(Map *map)
{
    if (get_hit_ground()) {
        if (m_dir == Right) {
            if (!check_collision(m_x + get_attribute("right"),
                                 m_y + get_attribute("bottom") + 1, map)) {
                set_dir(Left);
            }
        }
        else if (m_dir == Left) {
            if (!check_collision(m_x + get_attribute("left"),
                                 m_y + get_attribute("bottom") + 1, map)) {
                set_dir(Right);
            }
        }
    }
}

void Crawler::fire()
{
    bool result = false;

    unsigned n = m_bullets.size();
    for (int i = 0; i < n; i++) {
        if (!m_bullets[i]->get_active()) {
            int dx = get_attribute("bullet_speed");
            if (get_dir() == Right) {
                result = m_bullets[i]->fire(m_x + get_attribute("attack_right"),
                                            m_y + get_attribute("attack_medium"),
                                            dx, 0);
            }
            else {
                result = m_bullets[i]->fire(m_x + get_attribute("attack_left"),
                                            m_y + get_attribute("attack_medium"),
                                            -dx, 0);
            }

            if (result) {
                break;
            }
        }
    }
}

bool Crawler::get_visible(Map *map, int clip_x, int clip_y,
                          int clip_w, int clip_h) const
{
    bool result = false;

    if (m_bullets.size()) {
        result = true;
    }
    else {
        result = Object::get_visible(map, clip_x, clip_y, clip_w, clip_h);
    }

    return result;
}

void Crawler::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            face_reference();
            set_action(Move);
            if (get_hit_ground()) {
                if (m_jump_counter > 0 &&
                    m_jump_counter <= get_attribute("num_jumps")) {
                    set_attack();
                }
            }
            break;

        case Move:
            if (check_ahead(map)) {
                swap_move_dir();
            }
            check_ground(map);
            if (m_dir == Right) {
                set_vx(get_attribute("move_speed"));
            }
            else {
                set_vx(-get_attribute("move_speed"));
            }
            animate_move();

            if (m_bullets.size() &&
                m_attack_timer.check(get_attribute("attack_timer"))) {
                int dist = m_xref - get_front();
                if (abs(dist) < get_attribute("attack_distance")) {
                    m_attack_timer.reset();
                    set_attack();
                }
            }
            break;

        case Attack:
            if (++m_jump_counter <= get_attribute("num_jumps")) {
                set_jump(map);
            }
            else {
                fire();
                m_jump_counter = 0;
                reset_attack();
            }
            break;

        default:
            break;
    }

    // Move bullets
    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->move(map);
    }
}

void Crawler::draw(Surface *dest, Map *map,
                   int clip_x, int clip_y, int clip_w, int clip_h)
{
    Monster::draw(dest, map, clip_x, clip_y, clip_w, clip_h);

    // Draw bullets
    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}

