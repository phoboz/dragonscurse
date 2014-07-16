#ifndef _Menu_H
#define _Menu_H

#include <vector>
#include "phoboz/text.h"

class Menu {
public:
    enum PointerDirection { DirectionUp, DirectionDown };

    Menu(const char *fontname,
         const char *pointer, int pointer_index,
         MediaDB *media);

    void set_spacing(int spacing) { m_spacing = spacing; }
    bool add_option(const char *str, void *data = 0,
                    const Sprite *icon_spr = 0, int icon_index = 0);
    void* advance_pointer(PointerDirection dir);
    int get_option() const { return m_curr_option; }

    void draw(SDL_Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);
private:
    std::string m_fontname;
    MediaDB *m_media;
    Sprite *m_pointer_spr;
    int m_pointer_index;
    int m_curr_option;
    int m_spacing;
    std::vector<Text*> m_options;
};

#endif

