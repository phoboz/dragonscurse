#include "phoboz/color.h"

void Color::set_argb(int value)
{
    m_a = (value & 0xff000000) >> 24;
    m_r = (value & 0x00ff0000) >> 16;
    m_g = (value & 0x0000ff00) >> 8;
    m_b = (value & 0x000000ff);
}

void Color::set_named(Name name)
{
    m_a = 0xff;

    switch(name) {
        case Black:
            m_r = 0x00;
            m_g = 0x00;
            m_b = 0x00;
            break;

        case DarkGrey:
            m_r = 0x33;
            m_g = 0x33;
            m_b = 0x33;
            break;

        case Grey:
            m_r = 0x54;
            m_g = 0x54;
            m_b = 0x54;
            break;

        case White:
            m_r = 0xff;
            m_g = 0xff;
            m_b = 0xff;
            break;

        case Red:
            m_r = 0xff;
            m_g = 0;
            m_b = 0;
            break;

        case BrightGreen:
            m_r = 0x7f;
            m_g = 0xbf;
            m_b = 0x7f;
            break;

        default:
            m_r = 0xff;
            m_g = 0xff;
            m_b = 0xff;
            break;
    }
}

Color::operator SDL_Color() const
{
    SDL_Color col;

    col.r = m_r;
    col.g = m_g;
    col.b = m_b;

    return col;
}

