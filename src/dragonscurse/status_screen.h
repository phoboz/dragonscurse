#ifndef _StatusScreen_H
#define _StatusScreen_H

#include "phoboz/text.h"

class Status;
class MediaDB;

class StatusScreen {
public:
    StatusScreen(Status *status, MediaDB *media);

    void move();
    void draw(SDL_Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    static const int c_pts_dx = 80;

    Status *m_status;
    Text *m_ap_label;
    Text *m_ap_text;
    Text *m_dp_label;
    Text *m_dp_text;
    Text *m_cp_label;
    Text *m_cp_text;
};

#endif

