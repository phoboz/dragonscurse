#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "phoboz/sprite.h"
#include "phoboz/ctrl.h"
#include "phoboz/map.h"
#include "phoboz/fps_timer.h"
#include "phoboz/media_db.h"
#include "object.h"
#include "object_factory.h"
#include "world_db.h"
#include "world.h"
#include "statusbar.h"
#include "church.h"
#include "shop.h"
#include "hospital.h"
#include "main_menu.h"
#include "status_screen.h"
#include "key_list.h"
#include "arm_list.h"
#include "shield_list.h"
#include "armour_list.h"

enum State { StateMap, StateRoom, StateMainMenu, StateSubMenu };

static const int c_offset_y = 24;
static SDL_Surface *screen;
static int screen_width = 640;
static int screen_height = 480;
static Map *map = 0;
static MediaDB *media = 0;
static Player *player = 0;
static WorldDB *db = 0;
static World *world = 0;
static Room *room = 0;
Status *status = 0;
static Statusbar *statusbar = 0;
static MainMenu *main_menu = 0;
static SubMenu *sub_menu = 0;
static StatusScreen *status_screen = 0;
static State state;
static State world_state;

void set_state(State new_state)
{
    if (state < StateMainMenu) {
        world_state = state;
    }

    state = new_state;
}

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
        fprintf(stderr, "Fatal Error -- Unable to open audio!\n");
        return false;
    }

    if(Mix_Init(MIX_INIT_MOD) != MIX_INIT_MOD) {
        fprintf(stderr, "Fatal Error -- Unable to initialize mixer\n");
        return false;
    }

    Mix_Volume(-1, MIX_MAX_VOLUME);

    media = new MediaDB("media.xml");

    // Initialize font engine
    if(!Text::init()) {
        fprintf(stderr, "Fatal Error -- Unable to initialize font engine\n");
        return false;
    }

    return true;
}

bool load_area(const char *ar_name,
               bool new_game,
               const char *pl_name,
               int start_x = -1, int start_y = -1,
               const char *music = 0)
{
    if (std::string(ar_name) == std::string("Church")) {
        room = new Church(media, map->get_filename(),
                          player->get_x(), player->get_y());
        set_state(StateRoom);
        return true;
    }
    else if (std::string(ar_name).compare(0, 4, "Shop") == 0) {
        room = new Shop(ar_name, media, db,
                        map->get_filename(),
                        player->get_x(), player->get_y());
        set_state(StateRoom);
        return true;
    }
    else if (std::string(ar_name) == std::string("Hospital")) {
        room = new Hospital(media, db,
                            map->get_filename(),
                            player->get_x(), player->get_y());
        set_state(StateRoom);
        return true;
    }

    set_state(StateMap);

    map = media->get_map(ar_name);
    if (!map) {
        fprintf(stderr, "Fatal Error -- Unable to load map %s\n", ar_name);
        return false;
    }

    world = new World(map, media, db, music);

    if (start_x == -1) {
        start_x = map->get_numeric_property("start_x");
    }
    if (start_y == -1) {
        start_y = map->get_numeric_property("start_y") - c_offset_y;
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
        status->aquire_shape(player);
    }
    else {
        player->set_x(start_x);
        player->set_y(start_y);
    }
}

void move()
{
    if (state == StateMap) {
        Area *area = world->move(player, 0, Statusbar::get_height(),
                                 screen_width, screen_height);

        if (player->get_action() == Actor::HitPerished) {
            printf("Player perished\n");
            exit(0);
        }

        if (area) {
            load_area(area->get_name(),
                      area->get_type() == Area::TypeCurse, area->get_data(),
                      area->get_sx(), area->get_sy() - c_offset_y,
                      area->get_music());
        }
    }
    else if (state == StateMainMenu || state == StateSubMenu) {
        status_screen->move();
    }
}

void move_keydown(int key)
{
    if (state == StateRoom) {
        Area *area = room->move(key);

        if (area) {
            load_area(area->get_name(),
                      area->get_type() == Area::TypeCurse, area->get_data(),
                      area->get_sx(), area->get_sy(), area->get_music());
        }
    }
    else if (state == StateMainMenu) {
        switch(main_menu->move(key)) {
            case MainMenu::OptionLoad:
                delete main_menu;
                state = world_state;
                db->restore("autosave.sav", media);
                break;

            case MainMenu::OptionContinue:
                delete main_menu;
                state = world_state;
                break;

            case MainMenu::OptionKeyList:
                sub_menu = new KeyList(media, db->get_status());
                delete main_menu;
                set_state(StateSubMenu);
                break;

            case MainMenu::OptionArmList:
                sub_menu = new ArmList(media, db->get_status());
                delete main_menu;
                set_state(StateSubMenu);
                break;

            case MainMenu::OptionShieldList:
                sub_menu = new ShieldList(media, db->get_status());
                delete main_menu;
                set_state(StateSubMenu);
                break;

            case MainMenu::OptionArmourList:
                sub_menu = new ArmourList(media, db->get_status());
                delete main_menu;
                set_state(StateSubMenu);
                break;

            case MainMenu::OptionQuit:
                db->store("autosave.sav");
                exit(0);
                break;

            default:
                break;
        }
    }
    else if (state == StateSubMenu) {
        int i = sub_menu->move(key);
        if (i == 0) {
            main_menu = new MainMenu(media);
            set_state(StateMainMenu);
            delete sub_menu;
        }
    }
    else if (MainMenu::check_menu(key)) {
        main_menu = new MainMenu(media);
        set_state(StateMainMenu);
    }
}

void redraw()
{
    statusbar->draw(screen, screen_width, screen_height);
    if (state == StateRoom) {
        room->draw(screen, 0, Statusbar::get_height(),
                   0, 0, screen_width, screen_height);
    }
    else if (state == StateMap) {
        world->draw(screen, player, 0, Statusbar::get_height(),
                    screen_width, screen_height);
    }
    else if (state == StateMainMenu) {
        status_screen->draw(screen,
                            0, Statusbar::get_height(),
                            0, 0, screen_width, screen_height);
        main_menu->draw(screen, 0, Statusbar::get_height(),
                        0, 0, screen_width, screen_height);
    }
    else if (state == StateSubMenu) {
        status_screen->draw(screen, 0, Statusbar::get_height(),
                            0, 0, screen_width, screen_height);
        sub_menu->draw(screen,
                       0, Statusbar::get_height(),
                       0, 0, screen_width, screen_height);
    }
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

    // TODO: workaround for linker
    delete new Tmx::Map();

    db = new WorldDB("world.xml");
    if (!db) {
        fprintf(stderr, "Fatal Error -- Unable to load locks database\n");
        return 1;
    }

    // Set object prefix from world database
    Object::set_prefix(db->get_prefix());

    status = db->get_status();
    statusbar = new Statusbar(status, media);
    status->add_hearts(1);
    status->aquire_item((Item *) ObjectFactory::create_object(
                                     "ivory_sword.xml",
                                     media, "Item"));

    status->aquire_item((Item *) ObjectFactory::create_object(
                                     "ivory_shield.xml",
                                      media, "Item"));

    status->aquire_item((Item *) ObjectFactory::create_object(
                                     "ivory_armour.xml",
                                      media, "Item"));

    status->equip_item("ivory_sword.xml");
    status->equip_item("ivory_shield.xml");
    status->equip_item("ivory_armour.xml");

    status_screen = new StatusScreen(status, media);

    load_area(map_name, true, player_name, start_x, start_y);

    while (!done) {

        if (timer.expired(30)) {

            while (SDL_PollEvent(&event) ) {
                if (event.type == SDL_QUIT) {
                    done = 1;
                }

                if (event.type == SDL_KEYDOWN) {
                    move_keydown(event.key.keysym.sym);
                }
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

