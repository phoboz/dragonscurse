#include "morph.h"

Morph::Morph(const char *fn, int x, int y, Object::Direction dir)
    : Object(TypeMorph, x, y, dir),
      m_done(false)
{
    load(fn);

    if (m_dir == Right) {
        m_frame = get_attribute("right_start");
    }
    else if (m_dir == Left) {
        m_frame = get_attribute("left_start");
    }
}

void Morph::move(Map *map)
{
    if (m_anim_timer.expired(get_attribute("treshold"))) {
        if (m_dir == Right) {
            if (++m_frame == get_attribute("right_end")) {
                m_anim_timer.reset();
                m_done = true;
            }
        }
        else if (m_dir == Left) {
            if (++m_frame == get_attribute("left_end")) {
                m_anim_timer.reset();
                m_done = true;
            }
        }
        else {
            m_done = true;
        }
    }
}

