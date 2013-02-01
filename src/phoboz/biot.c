#include "pixel.h"
#include "biot.h"
#include "phoboz/sprite.h"

int biot(int index1, SPRITE *spr1,
	 int x1, int y1,
	 int index2, SPRITE *spr2,
	 int x2, int y2)
{
    int sx1, sy1, sx2, sy2;
    int cx1, cy1, cx2, cy2;
    COLOR c1, c2;
    int left1, left2, over_left;
    int right1, right2, over_right;
    int top1, top2, over_top;
    int bottom1, bottom2, over_bottom;
    int over_width, over_height;
    int i, j;

    left1 = x1;
    left2 = x2;
    right1 = x1 + spr1->w;
    right2 = x2 + spr2->w;
    top1 = y1;
    top2 = y2;
    bottom1 = y1 + spr1->h;
    bottom2 = y2 + spr2->h;

    // Trivial rejections:
    if (bottom1 < top2) return(0);
    if (top1 > bottom2) return(0);
  
    if (right1 < left2) return(0);
    if (left1 > right2) return(0);


    // Ok, compute the rectangle of overlap:
    if (bottom1 > bottom2) over_bottom = bottom2;
    else over_bottom = bottom1;
 
    if (top1 < top2) over_top = top2;
    else over_top = top1;

    if (right1 > right2) over_right = right2;
    else over_right = right1;

    if (left1 < left2) over_left = left2;
    else over_left = left1;

    over_width = over_right - over_left;
    over_height = over_bottom - over_top;

    sx1=1+(index1%spr1->nhsprites)*(spr1->w+1);
    sy1=1+(index1/spr1->nhsprites)*(spr1->h+1);

    sx2=1+(index2%spr2->nhsprites)*(spr2->w+1);
    sy2=1+(index2/spr2->nhsprites)*(spr2->h+1);


    // Now start scanning the whole rectangle of overlap,
    // checking the corresponding pixel of each object's
    // bitmap to see if they're both non-zero:

    cx1 = sx1 + over_left - x1;
    cy1 = sy1 + over_top - y1;
    cx2 = sx2 + over_left - x2;
    cy2 = sy2 + over_top - y2;

    for (j=0; j < over_height; j++) {
        for (i=0; i < over_width; i++) {
	    get_pixel(&c1, cx1 + i, cy1 + j, spr1->img);
	    get_pixel(&c2, cx2 + i, cy2 + j, spr2->img);
            if ((c1.a > 0) && (c2.a > 0)) return(1);
        }
    }


    // Worst case!  We scanned through the whole darn rectangle of overlap 
    // and couldn't find a single colliding pixel!

    return(0);

}

