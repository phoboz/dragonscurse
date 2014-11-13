#ifndef _Sprite_H
#define _Sprite_H

#include "phoboz/surface.h"

class Sprite {
public:
    Sprite() : m_loaded(false) { }
    Sprite(const char *fn, int w, int h, int margin, int spacing)
        : m_loaded(false), m_w(0), m_h(0), m_margin(0), m_spacing(0)
    {
        load(fn, w, h, margin, spacing);
    }
    ~Sprite();
    bool load(const char *fn, int w, int h, int margin, int spacing);
    bool get_loaded() const { return m_loaded; }
    int get_width() const { return m_w; }
    int get_height() const { return m_h; }
    int get_image_width() const { return m_img->get_width(); }
    int get_image_height() const { return m_img->get_height(); }
    Surface* get_image() const { return m_img; }
    void draw(Surface *dest,
              int x, int y, int index,
              int clip_x, int clip_y, int clip_w, int clip_h) const;
    bool check_collision(int index1, int x1, int y1,
                         const Sprite *spr2, int index2, int x2, int y2) const {
       return check_collision(index1, x1, y1,
                              0, 0, m_w, m_h,
                              spr2, index2, x2, y2,
                              0, 0, spr2->m_w, spr2->m_h);
    }
    bool check_collision(int index1, int x1, int y1,
                         int start_x1, int start_y1, int end_x1, int end_y1,
                         const Sprite *spr2, int index2, int x2, int y2) const {
       return check_collision(index1, x1, y1,
                              start_x1, start_y1, end_x1, end_y1,
                              spr2, index2, x2, y2,
                              0, 0, spr2->m_w, spr2->m_h);
    }
    bool check_collision(int index1, int x1, int y1,
                         const Sprite *spr2, int index2, int x2, int y2,
                         int start_x2, int start_y2, int end_x2, int end_y2) const {
       return check_collision(index1, x1, y1,
                              0, 0, m_w, m_h,
                              spr2, index2, x2, y2,
                              start_x2, start_y2, end_x2, end_y2);
    }
    bool check_collision(int index1, int x1, int y1,
                         int start_x1, int start_y1, int end_x1, int end_y1,
                         const Sprite *spr2, int index2, int x2, int y2,
                         int start_x2, int start_y2, int end_x2, int end_y2) const;

private:
    bool m_loaded;
    int m_w, m_h;
    int m_margin, m_spacing;
    int m_stride;
    int m_nvsprites, m_nhsprites;
    Surface *m_img;
};

#endif

