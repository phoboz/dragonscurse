#include "haunter.h"
#include <math.h>

bool Haunter::m_circle_init = false;
int Haunter::m_circle_x[c_num_steps];
int Haunter::m_circle_y[c_num_steps];


Haunter::Haunter(const char *fn, MediaDB *media, int x, int y, int w, int h,
                 Direction dir)
    : Monster(fn, media, x, y, dir),
      m_circle_index(0),
      m_w(w), m_h(h)
{
    if (!m_circle_init) {
        for (int i = 0; i < c_num_steps; i++) {
            m_circle_x[i] = int(16 * sin(2 * M_PI * i / c_num_steps));
            m_circle_y[i] = int(16 * cos(2 * M_PI * i / c_num_steps));
        }
        m_circle_init = true;
    }

    set_solid(false);
}

void Haunter::move(Map *map)
{
    switch(m_action) {
        case Still:
            m_center_x = m_x + m_w / 2;
            m_center_y = m_y + m_h - get_attribute("bottom");
            m_x = m_center_x;
            // TODO: Check if player is close enought
            set_action(Fall);
            break;

        case Move:
            m_circle_index += get_attribute("move_speed");
            if (m_circle_index >= c_num_steps) {
                m_circle_index = m_circle_index - c_num_steps;
            }
            set_x(m_center_x + m_w / 2 * m_circle_x[m_circle_index] / 16);
            set_y(m_center_y + m_w / 2 * m_circle_y[m_circle_index] / 16);
            break;

        case Fall:
            animate_move();
            if (m_y < m_center_y + m_w / 2) {
                m_y += get_attribute("fall_speed");
                if (m_y > m_center_y + m_w / 2) {
                    m_y = m_center_y + m_w / 2;
                }
            }
            else {
                set_action(Move);
            }
            break;

        case Hit:
        case HitPerish:
            process_hit();
            Monster::move(map);
            break;

        default:
            break;
    }
}

