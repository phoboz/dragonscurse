#ifndef _Body_H
#define _Body_H

#include "object.h"

class Body : public Object {
public:
    Body(Type type, int x = 0, int y = 0)
        : Object(type, x, y),
          m_ax(0), m_ay(0), m_vert_dir(VerticalNone),
          m_solid(true) { }
    Body(Type type, int x, int y, Direction dir)
        : Object(type, x, y, dir),
          m_ax(0), m_ay(0), m_vert_dir(VerticalNone),
          m_solid(true) { }

    void set_solid(bool solid) { m_solid = solid; }
    void set_speed(int vx, int vy);
    void set_accelration(int ax, int ay);
    virtual void set_move_dir(Direction dir);
    virtual void set_vertical_dir(VerticalDirection dir);

    virtual bool get_moving() const;

    virtual void move(Map *map);

protected:
    VerticalDirection m_vert_dir;

private:
    static const float c_sigma = 0.01;

    bool m_solid;
    float m_ax, m_ay;
    float m_vx, m_vy;
};

#endif

