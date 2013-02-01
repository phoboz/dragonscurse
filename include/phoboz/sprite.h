#ifndef _Sprite_H
#define _Sprite_H

#include "SDL.h"

class Sprite {
public:
    Sprite() : m_loaded(false) { }
    Sprite(const char *fn, int w, int h, int margin, int spacing)
        : m_loaded(false), m_w(0), m_h(0), m_margin(0), m_spacing(0)
    {
        load(fn, w, h, margin, spacing);
    }
    ~Sprite();
    bool load(const char *fn, int w, int h, int margIn, int spacing);
    bool get_loaded() const { return m_loaded; }
    int get_width() const { return m_w; }
    int get_height() const { return m_h; }
    int get_image_width() const { return m_img->w; }
    int get_image_height() const { return m_img->h; }
    SDL_Surface* get_image() const { return m_img; }
    void draw(SDL_Surface *dest,
              int x, int y, int index,
              int clip_x, int clip_y, int clip_w, int clip_h) const;
    bool check_collision(int index1, int x1, int y1,
                         const Sprite *spr2, int index2, int x2, int y2) const;
private:
    bool m_loaded;
    int m_w, m_h;
    int m_margin, m_spacing;
    int m_stride;
    int m_nvsprites, m_nhsprites;
    SDL_Surface *m_img;
};

#endif

