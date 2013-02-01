#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include "SDL.h"
#include "phoboz/sprite.h"
#include "pngfuncs.h"
#include <iostream>

struct Options {
public:
    std::string in_fn;
    int w, h;
    int margin;
    int spacing;
    std::string out_fn;
    int out_margin;
    int out_spacing;
    bool save;
};

static int screen_width = 640;
static int screen_height = 480;
static SDL_Surface *screen;
static Sprite *spr;

bool parseopt(Options *opt, int argc, char *argv[])
{
    opt->in_fn = std::string("");
    opt->w = 0;
    opt->h = 0;
    opt->margin = 0;
    opt->spacing = 0;
    opt->out_fn = std::string("");
    opt->out_margin = 1;
    opt->out_spacing = 1;
    opt->save = false;

    namespace po = boost::program_options;

    // Declare the supported options.
    po::options_description generic_options("Generic options");
    generic_options.add_options()
        ("help", "produce help message")
        ("width,w", po::value<int>(), "set sprite width")
        ("height,h", po::value<int>(), "set sprite height")
        ("margin,m", po::value<int>(), "set sprite margin")
        ("spacing,s", po::value<int>(), "set sprite spacing")
        ("output-file,o", po::value<std::string>(), "output file")
        ("output-margin", po::value<int>(), "set output margin")
        ("output-spacing", po::value<int>(), "set output spacing")
    ;

    po::options_description hidden_options("Hidden options");
    hidden_options.add_options()
        ("input-file", po::value<std::string>(), "input file")
    ;

    po::options_description cmdline_options;
    cmdline_options.add(generic_options).add(hidden_options);

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
              options(cmdline_options).positional(p).run(), vm);
    po::notify(vm);    

    if (vm.count("help")) {
        std::cout << generic_options << "\n";
        return false;
    }

    if (vm.count("width")) {
        opt->w = vm["width"].as<int>();
    }
    else {
        return false;
    }

    if (vm.count("height")) {
        opt->h = vm["height"].as<int>();
    }
    else {
        return false;
    }

    if (vm.count("margin")) {
        opt->margin = vm["margin"].as<int>();
    }

    if (vm.count("spacing")) {
        opt->spacing = vm["spacing"].as<int>();
    }

    if (vm.count("input-file")) {
        opt->in_fn = vm["input-file"].as<std::string>();
    }
    else {
        return false;
    }

    if (vm.count("output-file")) {
        opt->out_fn = vm["output-file"].as<std::string>();
        opt->save = true;
    }

    if (vm.count("output-margin")) {
        opt->out_margin = vm["output-margin"].as<int>();
    }

    if (vm.count("output-spacing")) {
        opt->out_spacing = vm["output-spacing"].as<int>();
    }

    return true;
}

bool init(void)
{
    // Initlaize SDL with video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Fatal Error -- Unable to initialize SDL: %s\n", SDL_GetError());
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

void redraw(SDL_Surface *surface, int margin, int spacing)
{
    const int w = spr->get_width();
    const int h = spr->get_height();
    const int ncol = (screen_width - margin) / (w + spacing);
    const int nrow = (screen_height - margin) / (h + spacing);

    for (int j = 0; j < nrow; j++) {
        for (int i = 0; i < ncol; i++) {
            int x = margin + i * (w + spacing);
            int y = margin + j * (h + spacing);

            SDL_Rect dest_rect;

            // Fill sprite frame and background
            if (i) {
                dest_rect.x = x - spacing;
                dest_rect.w = w + 2 * spacing;
            }
            else {
                dest_rect.x = 0;
                dest_rect.w = margin + w + spacing;
            }

            if (j) {
                dest_rect.y = y - spacing;
                dest_rect.h = h + 2 * spacing;
            }
            else {
                dest_rect.y = 0;
                dest_rect.h = margin + h + spacing;
            }
            SDL_FillRect(surface, &dest_rect, 0xffffffff);

            // Clear sprite background
            dest_rect.x = x;
            dest_rect.y = y;
            dest_rect.w = w;
            dest_rect.h = h;
            SDL_FillRect(screen, &dest_rect, 0x00ff0000);

            // Draw sprite
            spr->draw(surface, x, y, i + j * ncol,
                      0, 0, screen_width, screen_height);
        }
    }
}

void flip(void)
{
  SDL_Flip(screen);
}

int main(int argc, char *argv[])
{
    SDL_Event event;
    bool done = false;

    Options opt;
    if (!parseopt(&opt, argc, argv)) {
        fprintf(stderr, "Usage is: %s [options] --width arg --height arg input-file\n", argv[0]);
        return 1;
    }

    spr = new Sprite(opt.in_fn.c_str(), opt.w, opt.h, opt.margin, opt.spacing);
    if (!spr->get_loaded()) {
        fprintf(stderr, "Error - Unable to load file %s\n", opt.in_fn.c_str());
        return 1;
    }

    if (!init()) {
        return 1;
    }

    while (!done) {

        while (SDL_PollEvent(&event) ) {
            if (event.type == SDL_QUIT) done = true;
        }

        redraw(screen, opt.out_margin, opt.out_spacing);
        if (opt.save) {
            SDL_Surface *src = spr->get_image();
            SDL_Surface *dest = SDL_ConvertSurface(screen, src->format, src->flags);
            if(png_save_surface((char *) opt.out_fn.c_str(), dest) < 0) {
                fprintf(stderr, "Error - Unable to save file %s\n", opt.out_fn.c_str());
            }
            SDL_FreeSurface(dest);
            opt.save = false;
        }
        flip();
    }

  return 0;
}

