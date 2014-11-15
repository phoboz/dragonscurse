#include "phoboz/music.h"

Music::~Music()
{
    if (m_loaded) {
        Mix_FreeMusic(m_m);
        m_loaded = false;
    }
}

bool Music::load(const char *fn)
{
    m_loaded = false;

    if (init()) {
        m_m = Mix_LoadMUS(fn);
        if (m_m) {
            m_loaded = true;
        }
    }

    return m_loaded;
}

bool Music::play(Loop loop)
{
    bool result = false;

    if (m_loaded) {
        if(Mix_PlayMusic(m_m, loop) != -1) {
            result = true;
        }
    }

    return result;
}

