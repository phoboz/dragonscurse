#ifndef _Body_H
#define _Body_H

#include "object.h"

class Body : public Object {
public:
    Body(Type type, int x = 0, int y = 0, Direction dir = None)
        : Object(type, x, y, dir),
          m_ax(0.0f), m_ay(0.0f), m_vx(0.0f), m_vy(0.0f),
          m_solid(true), m_lock_dir(false),
          m_vert_dir(VerticalNone) { }

    int get_vx() const { return int(m_vx); }
    int get_vy() const { return int(m_vx); }

    void set_solid(bool solid) { m_solid = solid; }
    void set_lock_direction(bool lock_dir) { m_lock_dir = lock_dir; }
    void set_vx(int value) { m_vx = float(value); }
    void set_vy(int value) { m_vy = float(value); }
    void set_ax(int value) { m_ax = float(value) * c_g; }
    void set_ay(int value) { m_ay = float(value) * c_g; }
    void set_speed(int vx, int vy);
    void set_accelration(int ax, int ay);
    virtual void set_dir(Direction dir);

    virtual bool get_moving();
    bool get_fall() const { return (m_vert_dir == VerticalDown); }

    virtual void move(Map *map);

    void log() const;

private:
    static const float c_sigma = 0.01f;
    static const float c_g = 0.1f;

    bool m_solid;
    bool m_lock_dir;
    VerticalDirection m_vert_dir;
    float m_ax, m_ay;
    float m_vx, m_vy;
};

#endif

