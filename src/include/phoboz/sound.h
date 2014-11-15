#ifndef _Sound_H
#define _Sound_H

#include "SDL_mixer.h"

class Sound {
public:
    enum Channel { ChannelAuto = -1 };
    enum Loop { LoopForever = -1, LoopNone = 0 };

    static bool init();

private:
    static bool m_initialized;
};

#endif

