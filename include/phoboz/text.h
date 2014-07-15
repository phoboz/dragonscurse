#ifndef _Text_H
#define _Text_H

#include <vector>
#include "SDL_ttf.h"
#include "phoboz/media_db.h"

// Hidden
struct TextLine;

class Text {
public:
    Text(const char *fontname, MediaDB *media,
         const Sprite *icon_spr = 0, int icon_index = 0);

    ~Text();

    static bool init();
    static TTF_Font* load_font(const char *fn, int size);

    void set_icon(const char *icon, int icon_index);
    bool add_line(const char *str);
    bool add_text(const char *str);

    int get_height() const;

    void draw(SDL_Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    TextLine* new_line(const char *str);

    static bool m_initialized;
    MediaDB *m_media;
    TTF_Font *m_font;
    Sprite *m_icon_spr;
    int m_icon_index;
    std::vector<TextLine*> m_lines;
};

#endif

