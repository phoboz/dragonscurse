#include "room.h"

Room::Room(const char *image, MediaDB *media, int sx, int sy)
    : m_media(media),
      m_sx(sx), m_sy(sy)
{
    m_spr = m_media->get_sprite(image);
    if (m_spr) {
        m_loaded = true;
    }
    else {
        m_loaded = false;
    }

    m_media->play_music("room.ogg");
}

Room::~Room()
{
    if (m_loaded) {
        m_loaded = false;
        m_media->leave_sprite(m_spr);
    }
}

