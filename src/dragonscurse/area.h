#ifndef _Area_H
#define _Area_H

#include <string>

class Actor;

class Area {
public:
    enum Type { TypeWarp };

    Area(const char *name, const char *type,
         int x, int y, int w, int h, int sx, int sy);

    bool inside(Actor *actor) const;

    std::string get_name() const { return m_name; }
    Type get_type() const { return m_type; }
    int get_x1() const { return m_x; }
    int get_y1() const { return m_y; }
    int get_x2() const { return m_x + m_w; }
    int get_y2() const { return m_y + m_h; }
    int get_sx() const { return m_sx; }
    int get_sy() const { return m_sy; }

private:
    std::string m_name;
    Type m_type;
    int m_x, m_y;
    int m_w, m_h;
    int m_sx, m_sy;
};

#endif

