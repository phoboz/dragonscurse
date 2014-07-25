#include "object.h"

class Body : public Object {
public:
    Body(Type type, int x = 0, int y = 0)
        : Object(type, x, y),
          m_ax(0), m_ay(0), m_vert_dir(VerticalNone) { }
    Body(Type type, int x, int y, Direction dir)
        : Object(type, x, y, dir),
          m_ax(0), m_ay(0), m_vert_dir(VerticalNone) { }

    void set_speed(int vx, int vy);
    void set_accelration(int ax, int ay);
    virtual void set_move_dir(Direction dir);
    virtual void set_vertical_dir(VerticalDirection dir);

    bool is_moving() const { return (m_vx || m_vy); }

    virtual void move(Map *map);

protected:
    VerticalDirection m_vert_dir;

private:
    int m_ax, m_ay;
    int m_vx, m_vy;
};

