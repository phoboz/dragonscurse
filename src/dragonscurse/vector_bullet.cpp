#include <math.h>
#include "vector_bullet.h"

bool VectorBullet::fire(int x, int y, int dx, int dy)
{
    bool result = false;

    if (!get_active() && get_ready()) {
        set_x(x);
        set_y(y);
        set_speed(dx, dy);
        reload(true);
        result = true;
    }

    return result;
}

