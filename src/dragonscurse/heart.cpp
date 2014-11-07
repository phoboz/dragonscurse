#include "heart.h"

Heart::Heart(MediaDB *media)
    : m_media(media), m_loaded(false), m_hp(c_hp_per_heart)
{
    m_spr = media->get_sprite("heart_outline.png");
    if (m_spr) {
        m_loaded = true;
    }
    else {
        m_loaded = false;
    }
}

void Heart::draw(SDL_Surface *surface, int x, int y,
                 int clip_x, int clip_y, int clip_w, int clip_h)
{
    SDL_Rect dest_rect;
    int w = m_spr->get_width();
    int q = w * m_hp;
    q /= c_hp_per_heart;

    // Draw red part
    dest_rect.x = x;
    dest_rect.y = y;
    dest_rect.w = q;
    dest_rect.h = w;
    SDL_FillRect(surface, &dest_rect, 0x00ff0000);

    // Draw black part
    dest_rect.x = x + q;
    dest_rect.y = y;
    dest_rect.w = w - q;
    dest_rect.h = w;
    SDL_FillRect(surface, &dest_rect, 0x00000000);

    m_spr->draw(surface, x, y, 0,
                clip_x, clip_y, clip_w, clip_h);
}

