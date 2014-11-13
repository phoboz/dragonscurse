#ifndef _Rect_H
#define _Rect_H

#include "SDL.h"

class Rect {
public:
    Rect(int x, int y, int w, int h)
        : m_x(x),
          m_y(y),
          m_w(w),
          m_h(h) { }

    operator SDL_Rect() const;

private:
    int m_x, m_y;
    int m_w, m_h;
};

#endif

