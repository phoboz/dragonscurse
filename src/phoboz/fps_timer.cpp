#include "SDL.h"
#include "phoboz/fps_timer.h"

bool FpsTimer::expired(int frame_rate)
{
    bool result;
    float curr_time = SDL_GetTicks() * 0.001f;

    if((curr_time - m_time) > (1.0f / frame_rate)) {
        m_time = curr_time;
        result = true;
    }
    else {
        result = false;
    }

    return result;
}

