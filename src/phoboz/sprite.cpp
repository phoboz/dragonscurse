#include <iostream>
#include <stdlib.h>
#include "SDL_image.h"
#include "phoboz/sprite.h"
#include "pixel.h"

Sprite::~Sprite()
{
    if (m_loaded) {
        m_loaded = false;
        SDL_FreeSurface(m_img);
    }
}

bool Sprite::load(const char *fn, int w, int h, int margin, int spacing)
{
    SDL_Surface* tmp = IMG_Load(fn);
    if (tmp) {
      m_img = SDL_DisplayFormatAlpha(tmp);
      SDL_FreeSurface(tmp);
      if (!m_img) {
          m_loaded = false;
          return m_loaded;
      }
      m_w = w;
      m_h = h;
      m_margin = margin;
      m_spacing = spacing;
      m_stride = (m_img->w - margin) / (w + spacing);
      m_loaded = true;
    }
    else {
      m_loaded = false;
    }

    return m_loaded;
}

void Sprite::draw(SDL_Surface *dest,
                  int x, int y, int index,
		  int clip_x, int clip_y, int clip_w, int clip_h) const
{
    int tx, ty;
    int bx, by, bw, bh;
    SDL_Rect dest_rect, src_rect;

    // Check if loaded
    if (!m_loaded) {
        return;
    }

    // Cache and precalculate variables
    tx = x;
    ty = y;
    bx = 0;
    by = 0;
    bw = m_w;
    bh = m_h;

    // Test if sprite is complete outside clipping box
    if((tx + m_w <= clip_x) || (tx >= clip_w) ||
       (ty + m_h <= clip_y) || (ty >= clip_h)) {
        return;
    }

    // Get starting position in pixels of indexed tile
    int col = index % m_stride;
    int row = index / m_stride;
    int sx = m_margin + (m_spacing + m_w) * col;
    int sy = m_margin + (m_spacing + m_h) * row;

    // Test if clipping is needed
    if(tx >= clip_x || tx + m_w <= clip_w ||
       ty >= clip_y || ty + m_h <= clip_h ) {

        // x left of clipping box
        if(tx < clip_x) {
            bx = clip_x - tx;
            bw = m_w - bx;
            tx = clip_x;
        }

        // x+w right of clipping box
        else if(tx + m_w > clip_w) {
            bx = 0;
            bw = clip_w - tx;
        }

        // y over of clipping box
        if(ty < clip_y) {
            by = clip_y - ty;
            bh = m_h - by;
            ty = clip_y;
        }

        // y+h under clipping box
        else if(ty + m_h > clip_h) {
            by = 0;
            bh = clip_h - ty;
        }
    }

    // Calculate rects for SDL blitter
    dest_rect.x = tx;
    dest_rect.y = ty;

    src_rect.x = sx + bx;
    src_rect.y = sy + by;
    src_rect.w = bw;
    src_rect.h = bh;

    // Draw sprite
    SDL_BlitSurface(m_img, &src_rect, dest, &dest_rect);
}

bool Sprite::check_collision(int index1, int x1, int y1,
                             int left, int top, int right, int bottom,
                             const Sprite *spr2, int index2, int x2, int y2) const
{
    int left1, left2, over_left;
    int right1, right2, over_right;
    int top1, top2, over_top;
    int bottom1, bottom2, over_bottom;
    int over_width, over_height;
    int i, j;

    left1 = x1 + left;
    left2 = x2;
    right1 = x1 + right;
    right2 = x2 + spr2->m_w;
    top1 = y1 + top;
    top2 = y2;
    bottom1 = y1 + bottom;
    bottom2 = y2 + spr2->m_h;

    // Trivial rejections:
    if (bottom1 < top2) {
        return false;
    }
    if (top1 > bottom2) {
        return false;
    }
  
    if (right1 < left2) {
        return false;
    }
    if (left1 > right2) {
        return false;
    }

    // Ok, compute the rectangle of overlap:
    if (bottom1 > bottom2) {
        over_bottom = bottom2;
    }
    else {
        over_bottom = bottom1;
    }
 
    if (top1 < top2) {
        over_top = top2;
    }
    else {
        over_top = top1;
    }

    if (right1 > right2) {
        over_right = right2;
    }
    else {
        over_right = right1;
    }

    if (left1 < left2) {
        over_left = left2;
    }
    else {
        over_left = left1;
    }

    // Get starting position in pixels of indexed tile
    int col1 = index1 % m_stride;
    int row1 = index1 / m_stride;
    int sx1 = m_margin + (m_spacing + m_w) * col1;
    int sy1 = m_margin + (m_spacing + m_h) * row1;

    int col2 = index2 % spr2->m_stride;
    int row2 = index2 / spr2->m_stride;
    int sx2 = spr2->m_margin + (spr2->m_spacing + spr2->m_w) * col2;
    int sy2 = spr2->m_margin + (spr2->m_spacing + spr2->m_h) * row2;

    over_width = over_right - over_left;
    over_height = over_bottom - over_top;

    // Now start scanning the whole rectangle of overlap,
    // checking the corresponding pixel of each object's
    // bitmap to see if they're both non-zero:

    int cx1 = sx1 + over_left - x1;
    int cy1 = sy1 + over_top - y1;
    int cx2 = sx2 + over_left - x2;
    int cy2 = sy2 + over_top - y2;

    Color c1, c2;
    for (j = 0; j < over_height; j++) {
        for (i = 0; i < over_width; i++) {
	    get_pixel(&c1, cx1 + i, cy1 + j, m_img);
	    get_pixel(&c2, cx2 + i, cy2 + j, spr2->m_img);
            if ((c1.a > 0) && (c2.a > 0)) {
                return true;
            }
        }
    }


    // Worst case!  We scanned through the whole darn rectangle of overlap 
    // and couldn't find a single colliding pixel!

    return false;

}

