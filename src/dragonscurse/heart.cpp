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

void Heart::draw(Surface *surface, int x, int y,
                 int clip_x, int clip_y, int clip_w, int clip_h)
{
    SDL_Rect dest_rect;
    int w = m_spr->get_width();
    int q = w * m_hp;
    q /= c_hp_per_heart;

    // Draw red part
    Rect red_rect(x, y, q, w);
    Color red_col(Color::Red);
    surface->fill_rect(&red_rect, &red_col);

    // Draw black part
    Rect black_rect(x + q, y, w - q, w);
    Color black_col(Color::Black);
    surface->fill_rect(&black_rect, &black_col);

    // Overlay hollow hear outline
    m_spr->draw(surface, x, y, 0,
                clip_x, clip_y, clip_w, clip_h);
}

