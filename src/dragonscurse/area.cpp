#include <string.h>
#include "actor.h"
#include "area.h"

Area::Area(const char *name, const char *type, int x, int y, int w, int h)
    : Object(Object::TypeArea, x, y),
      m_name(name),
      m_h(h), m_w(w)
{
    if (strcmp(type, "warp") == 0) {
        m_type = TypeWarp;
    }
    else if (strcmp(type, "travel") == 0) {
        m_type = TypeTravel;
    }
    else {
        m_type = TypeUser;
        load(type);
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

void Area::draw(SDL_Surface *dest, Map *map,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    if (m_type == TypeUser) {
        Object::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}

