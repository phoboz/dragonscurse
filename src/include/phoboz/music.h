#ifndef _Music_H
#define _Music_H

#include "phoboz/sound.h"

class Music : public Sound {
public:
    Music(const char *fn) { load(fn); }

    ~Music();

    bool load(const char *fn);

    bool get_loaded() const { return m_loaded; }

    virtual bool play(Loop = LoopForever);

private:
    bool m_loaded;
    Mix_Music *m_m;
};

#endif

