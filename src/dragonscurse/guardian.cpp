#include "guardian.h"

Guardian::Guardian(const char *fn, MediaDB *media, int x, int y, Direction dir)
    : Monster(fn, media, x, y, dir)
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

bool Guardian::attack_object(Object *object)
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

void Guardian::fire()
{
    bool result = false;

    unsigned n = m_bullets.size();
    for (int i = 0; i < n; i++) {
        if (!m_bullets[i]->get_active()) {
            int dx = get_attribute("bullet_speed");
            if (get_reference() == Right) {
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

void Guardian::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            face_reference();
            break;

        case Move:
            face_reference();
            animate_move();

            if (m_attack_timer.check(get_attribute("attack_timer"))) {
                int dist = get_attribute("attack_distance");
                int x = m_xref - get_front();
                int y = m_yref - get_y();
                if (x * x + y * y < dist * dist) {
                    m_attack_timer.reset();
                    set_jump(map);
                    if (get_reference() == Right) {
                        set_vx(get_attribute("jump_forward"));
                    }
                    else {
                        set_vx(-get_attribute("jump_forward"));
                    }
                }
            }
            break;

        case Fall:
            fire();
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

void Guardian::draw(SDL_Surface *dest, Map *map,
                    int clip_x, int clip_y, int clip_w, int clip_h)
{
    Monster::draw(dest, map, clip_x, clip_y, clip_w, clip_h);

    // Draw bullets
    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}

