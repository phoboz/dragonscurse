#include "phoboz/rect.h"

Rect::operator SDL_Rect() const
{
    SDL_Rect rect;

    rect.x = m_x;
    rect.y = m_y;
    rect.w = m_w;
    rect.h = m_h;

    return rect;
}

