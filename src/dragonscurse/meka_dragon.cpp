#include <stdlib.h>
#include "meka_dragon.h"

MekaDragon::MekaDragon(const char *fn, MediaDB *media,
                       int x, int y, Direction dir)
    : Monster(fn, media, x, y, dir),
      m_horizontal_dir(HorizontalForward),
      m_bullet_index(0), m_attack_now(false)
{
    set_always_visible(true);
    set_lock_direction(true);

    const char* bullet_name = get_string("bullet");
    int num_bullets = get_attribute("num_bullets");

    for (int i = 0; i < num_bullets; i++) {
        Bullet *bullet = new Bullet(bullet_name, media);
        if (!bullet->get_loaded()) {
            exit(1);
        }
        m_bullets.push_back(bullet);
    }
}

bool MekaDragon::attack_actor(Actor *actor)
{
    bool result = false;
    int num_bullets = m_bullets.size();

    for (int i = 0; i < num_bullets; i++) {

        if (m_bullets[i]->hit_object(actor)) {
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

void MekaDragon::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            set_action(Move);
            break;

        case Move:
            if (m_horizontal_dir == HorizontalForward) {

                // TODO: Check if meka shall turn around
                //face_reference(get_attribute("turn_width"));
                if (get_reference() == Right) {
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

                face_reference(get_attribute("turn_width"));
                if (get_reference() == Right) {
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

                // TODO: Attack directly if pushed against wall
            }

            if (m_attack_now ||
                m_attack_timer.expired(get_attribute("attack_timer"))) {
                m_attack_timer.reset();
                m_attack_now = false;
                set_attack();
            }
            break;

        case MediumAttack:
            if (m_hit == HitNone) {
                if (m_idle_timer.check(get_attribute("attack_idle"))){
                    fire();
                }
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

