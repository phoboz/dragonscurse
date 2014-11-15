#include "phoboz/sound.h"

bool Sound::m_initialized = false;

bool Sound::init()
{
    bool result = false;

    if (m_initialized) {
        result = true;
    }
    else {
        int audio_rate = 44100;
        Uint16 audio_format = AUDIO_S16;
        int audio_channels = 1;
        int audio_buffers = 4096;
        if(Mix_OpenAudio(audio_rate, audio_format, audio_channels,
                         audio_buffers) >= 0) {
            if(Mix_Init(MIX_INIT_MOD) == MIX_INIT_MOD) {
                Mix_Volume(-1, MIX_MAX_VOLUME);
                m_initialized = true;
                result = true;
            }
        }
    }

    return result;
}

