#include <stdlib.h>
#include "material.h"

Material::Material(Type type, const char *fn, MediaDB *media, int x, int y)
    : Body(type, x, y),
      m_from_chest(false),
      m_action(Rise),
      m_ref_done(false)
{
    load(fn, media);

    m_frame = get_attribute("move_start");
}

void Material::face_reference()
{
    const Sprite *spr = get_sprite();
    int check_width = spr->get_width();

    if (abs(m_xref - get_front()) >= check_width) {
        if (m_xref > get_front()) {
            m_dir = Right;
        }
        else if (m_xref < get_front()) {
            m_dir = Left;
        }
    }
}

void Material::animate_move()
{
    if (m_anim_timer.expired(get_attribute("treshold"))) {
        m_anim_timer.reset();
        if (++m_frame > get_attribute("move_end")) {
            m_frame = get_attribute("move_start");
        }
    }
}

void Material::move(Map *map)
{
    if (!m_ref_done) {
        int dx;
        if (m_from_chest) {
            dx = get_attribute("chest_speed");
        }
        else {
            dx = get_attribute("move_speed");
        }
        if (get_reference() == Right) {
            set_speed(dx, -get_attribute("rise_speed"));
        }
        else {
            set_speed(-dx, -get_attribute("rise_speed"));
        }
        set_accelration(0, get_attribute("weight"));
        m_ref_done = true;
    }

    Body::move(map);
    if (is_moving()) {
        animate_move();
    }
    else {
        m_frame = get_attribute("move_still");
    }
}

