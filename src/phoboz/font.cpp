#include "phoboz/font.h"

bool Font::m_initialized = false;

bool Font::init()
{
    bool result = false;

    if (m_initialized) {
        result = true;
    }
    else {
        if(TTF_Init() != -1) {
            result = true;
        }
    }

    return result;
}

bool Font::load(const char *fn, int size)
{
    m_loaded = false;

    if (init()) {
        m_f = TTF_OpenFont(fn, size);
        if (m_f) {
            m_loaded = true;
        }
    }

    return m_loaded;
}

Surface* Font::get_surface(const char *str, Color *color) const
{
    return new Surface(TTF_RenderText_Solid(m_f, str, *color));
}

void Font::get_dimensions(int *w, int *h, const char *str)
{
    TTF_SizeText(m_f, str, w, h);
}

