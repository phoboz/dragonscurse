#ifndef _Statusbar_H
#define _Statusbar_H

#include "phoboz/sprite.h"
#include "phoboz/text.h"
#include "status.h"

class Statusbar {
public:
    Statusbar(Status *status, MediaDB *media);

    static int get_height() { return c_height; }

    void draw(SDL_Surface *surface, int screen_width, int screen_height);

private:
    static int c_height;
    Status *m_status;
    MediaDB *m_media;
    bool m_loaded;
    Sprite *m_heart_spr;
    Text *m_gold_label;
    Text *m_gold_text;
};

#endif

