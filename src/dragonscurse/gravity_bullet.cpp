#include <math.h>
#include "gravity_bullet.h"

bool GravityBullet::fire(int x, int y, int dx, int dy)
{
    bool result = false;

    if (!get_active() && get_ready()) {
        set_x(x);
        set_y(y);
        set_speed(dx, dy);
        set_accelration(0, get_attribute("weight"));
        reload(true);
        result = true;
    }

    return result;
}

