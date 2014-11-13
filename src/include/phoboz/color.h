#ifndef _Color_h
#define _Color_h

#include "SDL.h"

class Color
{
public:
    Color()
        : m_r(0),
          m_g(0),
          m_b(0),
          m_a(0) { }

    Color(int r, int g, int b, int a)
        : m_r(r),
          m_g(g),
          m_b(b),
          m_a(a) { }

    Color(int rgba) { set_argb(rgba); }

    void set_r(unsigned char value) { m_r = value; }
    void set_g(unsigned char value) { m_g = value; }
    void set_b(unsigned char value) { m_b = value; }
    void set_a(unsigned char value) { m_a = value; }

    void set_argb(int value);

    unsigned char get_r() const { return m_r; }
    unsigned char get_g() const { return m_g; }
    unsigned char get_b() const { return m_b; }
    unsigned char get_a() const { return m_a; }

    operator SDL_Color() const;

private:
    unsigned char m_r, m_g, m_b, m_a;
};

#endif

