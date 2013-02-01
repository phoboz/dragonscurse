#include "pixel.h"

void get_pixel(Color *c, int x, int y, SDL_Surface *surface)
{
    /* Extracting color components from a 32-bit color value */
    SDL_PixelFormat *fmt;
    Uint32 temp, *pixel;

    fmt=surface->format;
    SDL_LockSurface(surface);
    pixel=(Uint32*)surface->pixels+y*surface->pitch/4+x;
    SDL_UnlockSurface(surface);

    /* Get Red component */
    temp=*pixel&fmt->Rmask; /* Isolate red component */
    temp=temp>>fmt->Rshift;/* Shift it down to 8-bit */
    temp=temp<<fmt->Rloss; /* Expand to a full 8-bit number */
    c->r=(Uint8)temp;

    /* Get Green component */
    temp=*pixel&fmt->Gmask; /* Isolate green component */
    temp=temp>>fmt->Gshift;/* Shift it down to 8-bit */
    temp=temp<<fmt->Gloss; /* Expand to a full 8-bit number */
    c->g=(Uint8)temp;

    /* Get Blue component */
    temp=*pixel&fmt->Bmask; /* Isolate blue component */
    temp=temp>>fmt->Bshift;/* Shift it down to 8-bit */
    temp=temp<<fmt->Bloss; /* Expand to a full 8-bit number */
    c->b=(Uint8)temp;

    /* Get Alpha component */
    temp=*pixel&fmt->Amask; /* Isolate alpha component */
    temp=temp>>fmt->Ashift;/* Shift it down to 8-bit */
    temp=temp<<fmt->Aloss; /* Expand to a full 8-bit number */
    c->a=(Uint8)temp;
}

