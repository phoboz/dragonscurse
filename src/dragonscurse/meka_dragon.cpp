#include <stdlib.h>
#include "meka_dragon.h"

MekaDragon::MekaDragon(const char *fn, MediaDB *media,
                       int x, int y, Direction dir)
    : Monster(fn, media, x, y, dir),
      m_horizontal_dir(HorizontalForward),
      m_bullet_index(0), m_attack_now(false)
{
    set_always_visible(true);
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

bool MekaDragon::attack_object(Object *object)
{
    bool result = false;
    int num_bullets = m_bullets.size();

    for (int i = 0; i < num_bullets; i++) {

        if (m_bullets[i]->hit_object(object)) {
            result = true;
            break;
        }
    }

    return result;
}

void MekaDragon::fire()
{
    if (m_fire_timer.expired(get_attribute("fire_next"))) {
        if (m_bullet_index < m_bullets.size()) {
            if (m_dir == Right) {
                m_bullets[m_bullet_index]->fire(
                    m_x + get_attribute("attack_right"),
                    m_y + get_attribute("attack_medium"),
                    get_attribute("fire_dx"),
                    get_attribute("fire_dy"));
            }
            else if (m_dir == Left) {
                m_bullets[m_bullet_index]->fire(
                    m_x + get_attribute("attack_left"),
                    m_y + get_attribute("attack_medium"),
                    -get_attribute("fire_dx"),
                    get_attribute("fire_dy"));
            }
            m_bullet_index++;
        }
        else {
            m_bullet_index = 0;
            m_idle_timer.reset();
            set_action(Move);
            reset_attack();
        }
    }
}

bool MekaDragon::get_visible(Map *map, int clip_x, int clip_y,
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

void MekaDragon::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            set_action(Move);
            break;

        case Move:
            face_reference(get_attribute("turn_width"));
            set_lock_direction(true);
            if (m_horizontal_dir == HorizontalForward) {

                if (m_dir == Right) {
                    set_vx(get_attribute("move_speed"));
                }
                else {
                    set_vx(-get_attribute("move_speed"));
                }
                animate_move();

                if (abs(m_xref - m_x) < get_attribute("attack_distance")) {
                    m_horizontal_dir = HorizontalBackward;
                }
            }
            else if (m_horizontal_dir == HorizontalBackward) {

                if (m_dir == Right) {
                    set_vx(-get_attribute("move_speed"));
                }
                else {
                    set_vx(get_attribute("move_speed"));
                }
                animate_move();

                if (abs(m_xref - m_x) > get_attribute("retreat_distance") ||
                    check_behind(map)) {
                    m_horizontal_dir = HorizontalForward;
                }
            }

            if (m_attack_now ||
                m_attack_timer.expired(get_attribute("attack_timer"))) {
                m_attack_timer.reset();
                m_attack_now = false;
                set_attack();
            }
            break;

        case Attack:
            if (m_idle_timer.check(get_attribute("attack_idle"))){
                fire();
            }
            break;

        case Hit:
            m_idle_timer.reset();
            m_attack_now = true;
            break;

        default:
            break;
    }

    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->move(map);
    }
}

void MekaDragon::draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h)
{
    Monster::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}

