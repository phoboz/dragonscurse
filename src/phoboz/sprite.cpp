#include <iostream>
#include <stdlib.h>
#include "phoboz/sprite.h"

Sprite::~Sprite()
{
    if (m_loaded) {
        delete m_img;
        m_loaded = false;
    }
}

bool Sprite::load(const char *fn, int w, int h, int margin, int spacing)
{
    m_img = new Surface(fn);
    if (m_img && m_img->get_loaded()) {
        m_w = w;
        m_h = h;
        m_margin = margin;
        m_spacing = spacing;
        m_stride = (m_img->get_width() - margin) / (w + spacing);
        m_loaded = true;
    }
    else {
        m_loaded = false;
    }

    return m_loaded;
}

void Sprite::draw(Surface *dest,
                  int x, int y, int index,
		  int clip_x, int clip_y, int clip_w, int clip_h) const
{
    int tx, ty;
    int bx, by, bw, bh;

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

    // Draw sprite
    Rect dest_rect(tx, ty, 0, 0);
    Rect src_rect(sx + bx, sy + by, bw, bh);
    m_img->draw(&src_rect, dest, &dest_rect);
}

bool Sprite::check_collision(int index1, int x1, int y1,
                             int start_x1, int start_y1, int end_x1, int end_y1,
                             const Sprite *spr2, int index2, int x2, int y2,
                             int start_x2, int start_y2, int end_x2, int end_y2) const
{
    int left1, left2, over_left;
    int right1, right2, over_right;
    int top1, top2, over_top;
    int bottom1, bottom2, over_bottom;
    int over_width, over_height;
    int i, j;

    left1 = x1 + start_x1;
    left2 = x2 + start_x2;
    right1 = x1 + end_x1;
    right2 = x2 + end_x2;
    top1 = y1 + start_y1;
    top2 = y2 + start_y2;
    bottom1 = y1 + end_y1;
    bottom2 = y2 + end_y2;

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
	    m_img->get_pixel(&c1, cx1 + i, cy1 + j);
	    spr2->m_img->get_pixel(&c2, cx2 + i, cy2 + j);
            if ((c1.get_a() > 0) && (c2.get_a() > 0)) {
                return true;
            }
        }
    }


    // Worst case!  We scanned through the whole darn rectangle of overlap 
    // and couldn't find a single colliding pixel!

    return false;

}

