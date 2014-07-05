#include "world_db.h"
#include "curse.h"

Curse::Curse(ObjectInfo *info, MediaDB *media)
    : Object(Object::TypeCurse),
      m_world_key(info->key),
      m_player(std::string(info->data.curse.player)),
      m_destination(std::string(info->data.curse.destination)),
      m_sx(info->data.curse.start_x),
      m_sy(info->data.curse.start_y),
      m_anim_dir(AnimUp)
{
    load(info->data.curse.name, media);
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

