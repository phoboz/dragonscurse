#include "phoboz/color.h"

void Color::set_argb(int value)
{
    m_a = (value & 0xff000000) >> 24;
    m_r = (value & 0x00ff0000) >> 16;
    m_g = (value & 0x0000ff00) >> 8;
    m_b = (value & 0x000000ff);
}

Color::operator SDL_Color() const
{
    SDL_Color col;

    col.r = m_r;
    col.g = m_g;
    col.b = m_b;

    return col;
}

