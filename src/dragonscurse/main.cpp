#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDL.h"
#include "SDL_mixer.h"

#include "phoboz/sprite.h"
#include "phoboz/font.h"
#include "phoboz/ctrl.h"
#include "phoboz/map.h"
#include "phoboz/fps_timer.h"
#include "phoboz/media_db.h"
#include "object.h"
#include "object_factory.h"
#include "world_db.h"
#include "world.h"
#include "statusbar.h"

static SDL_Surface *screen;
static int screen_width = 640;
static int screen_height = 480;
static Map *map;
static MediaDB *media;
static Player *player;
static WorldDB *db;
static World *world;
static Font *font;

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

    // Initialize audio
    int audio_rate = 44100;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 1;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels,
                     audio_buffers) < 0) {
        fprintf(stderr, "Unable to open audio!\n");
        return false;
    }

    if(Mix_Init(MIX_INIT_MOD) != MIX_INIT_MOD) {
        fprintf(stderr, "Unable to initialize mixer\n");
        return false;
    }

    Mix_Volume(-1, MIX_MAX_VOLUME);

    media = new MediaDB("media.xml");

    font = new Font("fntdag8x8.png", media);
    if (!font->get_loaded()) {
        fprintf(stderr, "Unable to load font\n");
        return false;
    }

    return true;
}

bool load_area(const char *ar_name,
               bool new_game,
               const char *pl_name,
               int start_x = -1, int start_y = -1)
{
    Tmx::Map *tmx = new Tmx::Map();
    tmx->ParseFile(ar_name);
    map = new Map(tmx);
    if (!map->get_loaded()) {
        fprintf(stderr, "Fatal Error -- Unable to load map %s\n", ar_name);
        return false;
    }

    world = new World(map, media, db);

    const Tmx::PropertySet prop = tmx->GetProperties();
    if (start_x == -1) {
        start_x = prop.GetNumericProperty("start_x");
    }
    if (start_y == -1) {
        start_y = prop.GetNumericProperty("start_y");
    }

    if (new_game) {
        player = (Player *) ObjectFactory::create_object(pl_name, media,
                                                         "Player",
                                                         start_x, start_y,
                                                         Object::Right);
        if (!player->get_loaded()) {
            fprintf(stderr, "Fatal Error -- Unable to player %s\n", pl_name);
            return false;
        }
    }
    else {
        player->set_x(start_x);
        player->set_y(start_y);
    }
}

void move()
{
    Area *area = world->move(player, 0, Statusbar::get_height(),
                             screen_width, screen_height);

    if (area) {
        load_area(area->get_name(),
                  area->get_type() == Area::TypeCurse, area->get_data(),
                  area->get_sx(), area->get_sy());
    }
}

void redraw()
{
    Statusbar::draw(screen, screen_width, screen_height);
    font->draw(screen, 0, 0, "Welcome to monster world!",
               0, 0, screen_width, Statusbar::get_height());
    world->draw(screen, player, 0, Statusbar::get_height(),
                screen_width, screen_height);
}

void flip()
{
    SDL_Flip(screen);
}

int main(int argc, char *argv[])
{
    static char map_name[32];
    static char player_name[32];
    SDL_Event event;
    FpsTimer timer;
    int done = 0;
    int start_x = -1;
    int start_y = -1;

    if (argc > 1) {
        strcpy(map_name, argv[1]);
    }
    else {
        strcpy(map_name, "castle_01.tmx");
    }

    if (argc > 2) {
        strcpy(player_name, argv[2]);
    }
    else {
        strcpy(player_name, "human.xml");
    }

    if (argc > 4) {
        start_x = atoi(argv[3]);
        start_y = atoi(argv[4]);
    }

    if (!init()) {
        return 1;
    }

    db = new WorldDB("world.xml");
    if (!db) {
        fprintf(stderr, "Fatal Error -- Unable to load locks database\n");
        return 1;
    }

    load_area(map_name, true, player_name, start_x, start_y);

    while (!done) {

        if (timer.expired(60)) {

            while (SDL_PollEvent(&event) ) {
                if (event.type == SDL_QUIT) done = 1;
            }

            SDL_Rect dest_rect;
            dest_rect.x = 0;
            dest_rect.y = Statusbar::get_height();
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

