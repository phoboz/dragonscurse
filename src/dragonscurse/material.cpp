#include <iostream>
#include "material.h"

Material::Material(Type type, const char *fn, MediaDB *media, int x, int y)
    : Object(type, x, y),
      m_from_chest(false),
      m_action(Rise)
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
    const Tmx::Tileset *tileset = map->get_tileset(0);

    if (m_action == Rise) {
        m_dy = get_attribute("move_speed");
        check_above(map);
        if (!m_dy) {
            m_action = Fall;
        }
    }
    else {
        m_dy = get_attribute("weight");
        check_below(map);
        if (m_dy) {
            m_action = Fall;
        }
    }

    if (m_from_chest) {
        m_dx = get_attribute("chest_speed");
    }
    else {
        m_dx = get_attribute("horizontal_speed");
    }

    face_reference();
    check_ahead(map);
    if (!m_dx && !m_dy) {
        m_action = Still;
        m_frame = get_attribute("move_still");
    }

    if (m_dir == Right) {
        m_x += m_dx;
    }
    else if (m_dir == Left) {
        m_x -= m_dx;
    }

    if (m_action == Rise) {
        m_y -= m_dy;
    }
    else if (m_action == Fall) {
        m_y += m_dy;
    }

    if (m_action != Still) {
        animate_move();
    }
}

