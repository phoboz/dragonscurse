#include "waver.h"
#include <math.h>

bool Waver::m_wave_init = false;
int Waver::m_wave_y[c_num_steps];

Waver::Waver(const char *fn, MediaDB *media, int x, int y, Direction dir)
    : Monster(fn, media, x, y, dir),
      m_wave_index(0)

{
    if (!m_wave_init) {
        for (int i = 0; i < c_num_steps; i++) {
            m_wave_y[i] = int(16 * sin(2 * M_PI * i / c_num_steps));
        }
        m_wave_init = true;
    }
}

void Waver::move(Map *map)
{
    switch(m_action) {
        case Still:
            set_action(Move);
            break;

        case Move:
            face_reference(get_attribute("turn_width"));
            animate_move();
            if (m_dir == Right) {
                set_vx(get_move_speed(map));
            }
            else {
                set_vx(-get_move_speed(map));
            }

            m_wave_index += get_attribute("frequency");
            if (m_wave_index >= c_num_steps) {
                m_wave_index = m_wave_index - c_num_steps;
            }
            set_vy(get_attribute("amplitude") * m_wave_y[m_wave_index] / 16);
            Body::move(map);
            break;

        case Hit:
        case HitPerish:
            set_ay(0);
            set_vy(0);
            process_hit();
            Monster::move(map);
            break;

        default:
            break;
    }
}

