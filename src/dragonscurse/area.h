#ifndef _Area_H
#define _Area_H

#include <string>
#include "object.h"

class Actor;

class Area : public Object {
public:
    enum Type { TypeWarp, TypeTravel, TypeUser };

    Area(const char *name, const char *type, int x, int y, int w, int h);

    bool inside(Actor *actor) const;

    std::string get_name() const { return m_name; }
    Type get_type() const { return m_type; }
    int get_x1() const { return m_x; }
    int get_y1() const { return m_y; }
    int get_x2() const { return m_x + m_w; }
    int get_y2() const { return m_y + m_h; }
    int get_sx() const { return get_attribute("start_x"); }
    int get_sy() const { return get_attribute("start_y"); }

    virtual bool get_visible(Map *map, int clip_x, int clip_y,
                             int clip_w, int clip_h) const { return true; }
    virtual void move(Map *map) { }
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    std::string m_name;
    Type m_type;
    int m_w, m_h;
};

#endif

