#include <string.h>
#include "actor.h"
#include "area.h"

Area::Area(const char *name, const char *type,
           int x, int y, int w, int h, int sx, int sy)
    : m_name(name), m_x(x), m_y(y), m_h(h), m_w(w),
      m_sx(sx), m_sy(sy)
{
    if (strcmp(type, "Warp") == 0) {
        m_type = TypeWarp;
    }
}

bool Area::inside(Actor *actor) const
{
    bool result = false;
    int x = actor->get_front();
    int y = actor->get_bottom();

    // Check if inside
    if (x >= m_x && x <= m_x + m_w &&
        y >= m_y && y <= m_y + m_h) {
        result = true;
    }

    return result;
}

