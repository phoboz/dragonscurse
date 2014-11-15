#include "phoboz/sample.h"

Sample::~Sample()
{
    if (m_loaded) {
        Mix_FreeChunk(m_s);
        m_loaded = false;
    }
}

bool Sample::load(const char *fn)
{
    m_loaded = false;

    if (init()) {
        m_s = Mix_LoadWAV(fn);
        if (m_s) {
            m_loaded = true;
        }
    }

    return m_loaded;
}

bool Sample::play(Channel channel, Loop loop)
{
    bool result = false;

    if (m_loaded) {
        if(Mix_PlayChannel(channel, m_s, loop) != -1) {
            result = true;
        }
    }

    return result;
}

