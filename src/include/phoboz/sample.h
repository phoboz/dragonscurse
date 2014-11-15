#ifndef _Sample_H
#define _Sample_H

#include "phoboz/sound.h"

class Sample : public Sound {
public:
    Sample(const char *fn) { load(fn); }

    ~Sample();

    bool load(const char *fn);

    bool get_loaded() const { return m_loaded; }

    virtual bool play(Channel channel = ChannelAuto, Loop = LoopNone);

private:
    bool m_loaded;
    Mix_Chunk *m_s;
};

#endif

