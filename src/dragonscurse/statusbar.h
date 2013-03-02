#ifndef _Statusbar_H
#define _Statusbar_H

class Statusbar {
public:
    static int get_height() { return c_height; }
    static void draw(SDL_Surface *surface, int screen_width, int screen_height);

private:
    static int c_height;
};

#endif

