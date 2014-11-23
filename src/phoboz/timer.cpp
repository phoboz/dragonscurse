#include "SDL.h"
#include "phoboz/timer.h"

bool Timer::check(int treshold)
{
    bool result = false;

    if (m_enabled) {
        if (++m_counter >= treshold) {
            m_counter = treshold;
            result = true;
        }
    }

    return result;
}

bool Timer::expired(int treshold)
{
    bool result = false;

    if (m_enabled) {
        if (++m_counter == treshold) {
            m_counter = 0;
            result = true;
        }
    }

    return result;
}

