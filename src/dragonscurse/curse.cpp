#include "curse.h"

Curse::Curse(const char *fn, int key)
    : Object(Object::TypeCurse),
      m_world_key(key)
{
    load(fn);
}

void Curse::move(Map *map)
{
    if (m_anim_timer.expired(get_attribute("treshold"))) {
        if (m_anim_dir == AnimUp) {
            if (++m_frame == get_attribute("end")) {
                m_anim_dir = AnimDown;
            }
        }
        else if (m_anim_dir == AnimDown) {
            if (--m_frame == get_attribute("start")) {
                m_anim_dir = AnimUp;
            }
        }
    }
}

