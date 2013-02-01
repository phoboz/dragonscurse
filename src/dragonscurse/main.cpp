#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDL.h"

#include "phoboz/sprite.h"
#include "phoboz/ctrl.h"
#include "phoboz/map.h"
#include "phoboz/dragon.h"

static SDL_Surface *screen;
static int screen_width = 640;
static int screen_height = 480;
static Map *map;
static Object *player;

int init(const char *fn, const char *fn2)
{
  /* Initlaize SDL with video and sound if possible */
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "Fatal Error -- Unable to initialize SDL: %s\n", SDL_GetError());
    return 0;
  }

  /* Install exit function */
  atexit(SDL_Quit);

  /* Initialize screen, setup gfx mode */
  screen = SDL_SetVideoMode(screen_width, screen_height, 32,
                            SDL_HWSURFACE|SDL_DOUBLEBUF);
  if (screen == NULL) {
    fprintf(stderr, "Fatal Error -- Unable to set video mode: %s\n",
            SDL_GetError());
    return 0;
  }

    Tmx::Map *tmx = new Tmx::Map();
    tmx->ParseFile(fn);
    map = new Map(tmx);
    if (!map->get_loaded()) {
        fprintf(stderr, "Fatal Error -- Unable to load map\n");
        return 0;
    }

    player = new Dragon(fn2);
    if (!player->get_loaded()) {
        fprintf(stderr, "Fatal Error -- Unable to load sprite\n");
        return 0;
    }

  return 1;
}

void move(void)
{
    player->move(map);
    map->set_x(player->get_x() - screen_width / 2);
    map->set_y(player->get_y() - screen_height / 2);
}

void redraw(void)
{
    map->draw_layer(screen, 0, 0, screen_width, screen_height, 0);
    player->draw(screen, map, 0, 0, screen_width, screen_height);
}

void flip(void)
{
  SDL_Flip(screen);
}

int main(int argc, char *argv[])
{
  SDL_Event event;
  int done = 0;

  if (!init(argv[1], argv[2]))
    return 1;

  while (!done) {
    
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

  return 0;
}

