#ifndef _Heart_H
#define _Heart_H

#include "phoboz/media_db.h"
#include "phoboz/sprite.h"

class Heart {
public:
    Heart(MediaDB *media);

    void set_full() { m_hp = c_hp_per_heart; }
    void set_hp(int hp) { m_hp = hp; }
    void set_empty() { m_hp = 0; }

    static int get_hp_per_heart() { return c_hp_per_heart; }
    int get_hp() const { return m_hp; }
    int get_width() const { return m_spr->get_width(); }

    void draw(Surface *surface, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    static const int c_hp_per_heart = 100;

    MediaDB *m_media;
    bool m_loaded;
    Sprite *m_spr;
    int m_hp;
};

#endif

