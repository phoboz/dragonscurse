#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDL.h"

#include "phoboz/sprite.h"
#include "phoboz/ctrl.h"
#include "phoboz/map.h"
#include "phoboz/fps_timer.h"
#include "object.h"
#include "object_factory.h"
#include "world.h"

#define STATUSBAR_HEIGHT 36

static SDL_Surface *screen;
static int screen_width = 640;
static int screen_height = 480;
static Map *map;
static Player *player;
static World *world;

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

void draw_statusbar()
{
    SDL_Rect dest_rect;

    dest_rect.x = 0;
    dest_rect.y = 0;
    dest_rect.w = screen_width;
    dest_rect.h = STATUSBAR_HEIGHT - 2;
    SDL_FillRect(screen, &dest_rect, 0x77777777);

    dest_rect.x = 0;
    dest_rect.y = STATUSBAR_HEIGHT - 2;
    dest_rect.w = screen_width;
    dest_rect.h = 2;
    SDL_FillRect(screen, &dest_rect, 0x55555555);
}

void move(void)
{
    world->move(player, 0, STATUSBAR_HEIGHT, screen_width, screen_height);
}

void redraw(void)
{
    draw_statusbar();
    world->draw(screen, player, 0, STATUSBAR_HEIGHT, screen_width, screen_height);
}

void flip(void)
{
    SDL_Flip(screen);
}

int main(int argc, char *argv[])
{
    SDL_Event event;
    FpsTimer timer;
    int done = 0;
    char type[32];

    if (argc > 3) {
        strcpy(type, argv[3]);
    }
    else {
        strcpy(type, "Player");
    }

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

    world = new World(map, 0);

    const Tmx::PropertySet prop = tmx->GetProperties();
    int start_x = prop.GetNumericProperty("start_x");
    int start_y = prop.GetNumericProperty("start_y");

    player = (Player *) ObjectFactory::create_object(argv[2], type,
                                                     //6 * 32, 42 * 32,
                                                     //32, 6 * 32,
                                                     start_x, start_y,
                                                     Object::Right);
    if (!player->get_loaded()) {
        fprintf(stderr, "Fatal Error -- Unable to player %s\n", argv[2]);
        return 1;
    }

    while (!done) {

        if (timer.expired(60)) {

            while (SDL_PollEvent(&event) ) {
                if (event.type == SDL_QUIT) done = 1;
            }

            SDL_Rect dest_rect;
            dest_rect.x = 0;
            dest_rect.y = STATUSBAR_HEIGHT;
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

