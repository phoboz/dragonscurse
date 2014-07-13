#ifndef _Menu_H
#define _Menu_H

#include <vector>
#include "phoboz/text.h"

class Menu {
public:
    Menu(const char *fontname, MediaDB *media)
        : m_fontname(fontname),
          m_media(media) { }

    bool add_option(const char *str, const char *icon = 0, int icon_index = 0);

    void draw(SDL_Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);
private:
    std::string m_fontname;
    MediaDB *m_media;
    std::vector<Text*> m_options;
};

#endif

