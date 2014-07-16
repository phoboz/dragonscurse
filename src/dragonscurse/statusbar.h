#ifndef _Statusbar_H
#define _Statusbar_H

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
    Text *m_gold_label;
    Text *m_gold_text;
};

#endif

