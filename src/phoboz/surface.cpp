#include "SDL_image.h"
#include "phoboz/surface.h"

bool Surface::m_initialized = false;

bool Surface::init()
{
    bool result = false;

    if (m_initialized) {
        result = true;
    }
    else {
        if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
            atexit(SDL_Quit);
            m_initialized = true;
            result = true;
        }
    }

    return result;
}

Surface::~Surface()
{
    if (m_loaded) {
        SDL_FreeSurface(m_s);
        m_loaded = false;
    }
}

bool Surface::load(const char *fn)
{
    m_loaded = false;

    if (init()) {
        SDL_Surface* tmp = IMG_Load(fn);
        if (tmp) {
            m_s = SDL_DisplayFormatAlpha(tmp);
            SDL_FreeSurface(tmp);
            if (m_s) {
                m_loaded = true;
            }
        }
    }

    return m_loaded;
}

bool Surface::set_screen(int w, int h, bool fullscreen)
{
    m_loaded = false;

    if (init()) {
        int flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
        if (fullscreen) {
            flags |= SDL_FULLSCREEN;
        }

        m_s = SDL_SetVideoMode(w, h, 32, flags);
        if (m_s) {
            m_loaded = true;
        }
    }

    return m_loaded;
}

void Surface::get_pixel(Color *c, int x, int y)
{
    // Extracting color components from a 32-bit color value
    SDL_PixelFormat *fmt;
    Uint32 temp, *pixel;

    fmt = m_s->format;
    SDL_LockSurface(m_s);
    pixel= (Uint32 *) m_s->pixels + y * m_s->pitch / 4 + x;
    SDL_UnlockSurface(m_s);

    // Get Red component
    temp = *pixel & fmt->Rmask; // Isolate red component
    temp = temp >> fmt->Rshift; //Shift it down to 8-bit
    temp = temp << fmt->Rloss;  //Expand to a full 8-bit number
    c->set_r((Uint8) temp);

    // Get Green component
    temp = *pixel & fmt->Gmask; // Isolate green component
    temp = temp >> fmt->Gshift; // Shift it down to 8-bit
    temp = temp << fmt->Gloss;  // Expand to a full 8-bit number
    c->set_g((Uint8) temp);

    // Get Blue component
    temp = *pixel & fmt->Bmask; // Isolate blue component
    temp = temp >> fmt->Bshift; // Shift it down to 8-bit
    temp = temp << fmt->Bloss;  // Expand to a full 8-bit number
    c->set_b((Uint8) temp);

    // Get Alpha component
    temp = *pixel & fmt->Amask; // Isolate alpha component
    temp = temp >> fmt->Ashift; // Shift it down to 8-bit
    temp = temp << fmt->Aloss;  // Expand to a full 8-bit number
    c->set_a((Uint8) temp);
}

void Surface::fill_rect(Rect *rect, Color *c)
{
    SDL_Rect dest_rect = *rect;
    SDL_Color col = *c;
    int pixel = SDL_MapRGB(get_format(), col.r, col.g, col.b);
    SDL_FillRect(m_s, &dest_rect, pixel);
}

void Surface::draw(Rect *src_rect, Surface *dest, Rect *dest_rect)
{
    SDL_Rect sdl_src_rect = *src_rect;
    SDL_Rect sdl_dest_rect = *dest_rect;

    SDL_BlitSurface(m_s, &sdl_src_rect, dest->m_s, &sdl_dest_rect);
}

