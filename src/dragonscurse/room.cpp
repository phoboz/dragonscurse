#include "room.h"

Room::Room(const char *image, const char *font, MediaDB *media, int sx, int sy,
           int tx, int ty)
    : m_media(media),
      m_sx(sx), m_sy(sy),
      m_tx(tx), m_ty(ty)
{
    m_spr = m_media->get_sprite(image);
    if (m_spr) {
        m_loaded = true;
        m_media->play_music("room.ogg");
        m_text = new Text(font, media);
    }
    else {
        m_loaded = false;
    }
}

Room::~Room()
{
    if (m_loaded) {
        m_loaded = false;
        m_media->leave_sprite(m_spr);
        delete m_text;
    }
}

void Room::draw(SDL_Surface *dest, int x, int y,
          int clip_x, int clip_y, int clip_w, int clip_h)
{
    m_spr->draw(dest, x, y, 0, clip_x, clip_y, clip_w, clip_h);
    m_text->draw(dest, x + m_tx, y + m_ty);
}

