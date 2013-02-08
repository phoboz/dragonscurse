#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDL.h"

#include "phoboz/sprite.h"
#include "phoboz/ctrl.h"
#include "phoboz/map.h"
#include "phoboz/timer.h"
#include "phoboz/player.h"
#include "phoboz/dragon.h"
#include "phoboz/walker.h"

static SDL_Surface *screen;
static int screen_width = 640;
static int screen_height = 480;
static Map *map;
static Object *player = 0;
static Object *enemy = 0;

bool init()
{
    // Initlaize SDL with video and sound if possible
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Fatal Error -- Unable to initialize SDL: %s\n",
                SDL_GetError());
        return false;
    }

    // Install exit function
    atexit(SDL_Quit);

    // Initialize screen, setup gfx mode
    screen = SDL_SetVideoMode(screen_width, screen_height, 32,
                              SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (screen == NULL) {
        fprintf(stderr, "Fatal Error -- Unable to set video mode: %s\n",
                SDL_GetError());
        return false;
    }

    return true;
}

void move(void)
{
    if (player) {
        player->move(map);
        int map_x = player->get_x() - screen_width / 2;
        int map_y = player->get_y() - screen_height / 2;
        if (map_x < 0) {
            map_x = 0;
        }
        if (map_y < 0) {
            map_y = 0;
        }
        map->set_x(map_x);
        map->set_y(map_y);
    }

    if (enemy) {
        enemy->move(map);
    }
}

void redraw(void)
{
    map->draw_layer(screen, 0, 0, screen_width, screen_height, 0);
    if (player) {
        player->draw(screen, map, 0, 0, screen_width, screen_height);
    }
    if (enemy) {
        enemy->draw(screen, map, 0, 0, screen_width, screen_height);
    }
}

void flip(void)
{
    SDL_Flip(screen);
}

int main(int argc, char *argv[])
{
    SDL_Event event;
    Timer timer;
    int done = 0;

    if (!init()) {
        return 1;
    }

    Tmx::Map *tmx = new Tmx::Map();
    tmx->ParseFile(argv[1]);
    map = new Map(tmx);
    if (!map->get_loaded()) {
        fprintf(stderr, "Fatal Error -- Unable to load map %s\n", argv[1]);
        return 1;
    }

    if (argc > 2) {
        player = new Player(argv[2]);
        if (!player->get_loaded()) {
            fprintf(stderr, "Fatal Error -- Unable to player %s\n", argv[2]);
            return 1;
        }
    }

    if (argc > 3) {
        enemy = new Walker(argv[3], 22 * 32, 42 * 32, Object::Left);
        if (!enemy->get_loaded()) {
            fprintf(stderr, "Fatal Error -- Unable to enemy %s\n", argv[3]);
            return 1;
        }
    }

    while (!done) {

        if (timer.lock_fps(60)) {

            while (SDL_PollEvent(&event) ) {
                if (event.type == SDL_QUIT) done = 1;
            }

            SDL_Rect dest_rect;
            dest_rect.x = 0;
            dest_rect.y = 0;
            dest_rect.w = screen_width;
            dest_rect.h = screen_height;
            SDL_FillRect(screen, &dest_rect, 0x00000000);

            move();
            redraw();
            flip();
        }

    }

    return 0;
}

