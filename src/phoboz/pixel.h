#ifndef _Pixel_h
#define _Pixel_h

#include <SDL/SDL.h>

typedef struct
{
  unsigned char r, g, b, a;
} Color;

extern void get_pixel(Color *c, int x, int y, SDL_Surface *surface);

#endif

