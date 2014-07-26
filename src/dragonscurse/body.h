#ifndef _Body_H
#define _Body_H

#include "object.h"

class Body : public Object {
public:
    Body(Type type, int x = 0, int y = 0)
        : Object(type, x, y),
          m_ax(0.0f), m_ay(0.0f), m_vx(0.0f), m_vy(0.0f),
          m_solid(true) { }
    Body(Type type, int x, int y, Direction dir)
        : Object(type, x, y, dir),
          m_ax(0.0f), m_ay(0.0f), m_vx(0.0f), m_vy(0.0f),
          m_solid(true) { }

    void set_solid(bool solid) { m_solid = solid; }
    void set_vx(int value) { m_vx = float(value); }
    void set_vy(int value) { m_vy = float(value); }
    void set_ax(int value) { m_ax = float(value) * c_g; }
    void set_ay(int value) { m_ay = float(value) * c_g; }
    void set_speed(int vx, int vy);
    void set_accelration(int ax, int ay);
    virtual void set_dir(Direction dir);

    virtual bool get_moving() const;
    bool get_fall() const { return (m_vy > 0.0f); }

    virtual void move(Map *map);

private:
    static const float c_sigma = 0.01f;
    static const float c_g = 0.1f;

    bool m_solid;
    float m_ax, m_ay;
    float m_vx, m_vy;
};

#endif

