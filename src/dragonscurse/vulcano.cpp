#include <stdlib.h>
#include "vulcano.h"

void Vulcano::fire()
{
    bool result = false;

    unsigned n = m_bullets.size();
    for (int i = 0; i < n; i++) {
        if (!m_bullets[i]->get_active()) {
            int dx = rand() % (get_attribute("fire_dx") - 1) + 1;
            int dy = get_attribute("fire_dy");
            if (get_reference() == Right) {
                result = m_bullets[i]->fire(m_x, m_y, dx, -dy);
            }
            else {
                result = m_bullets[i]->fire(m_x, m_y, -dx, -dy);
            }

            if (result) {
                set_attack();
                break;
            }
        }
    }
}

