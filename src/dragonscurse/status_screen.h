#ifndef _StatusScreen_H
#define _StatusScreen_H

#include "phoboz/text.h"

class Status;
class MediaDB;

class StatusScreen {
public:
    StatusScreen(Status *status, MediaDB *media);

    void move();
    void draw(Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    static const int c_stat_dx = 80;
    static const int c_magic_dx = 170;
    static const int c_magic_dy = 120;

    Status *m_status;
    Text *m_ap_label;
    Text *m_ap_text;
    Text *m_dp_label;
    Text *m_dp_text;
    Text *m_cp_label;
    Text *m_cp_text;
    Text *m_fire_label;
    Text *m_fire_text;
    Text *m_tornado_label;
    Text *m_tornado_text;
    Text *m_arrow_label;
    Text *m_arrow_text;
    Text *m_boomerang_label;
    Text *m_boomerang_text;
    Text *m_thunder_label;
    Text *m_thunder_text;
};

#endif

