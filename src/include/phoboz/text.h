#ifndef _Text_H
#define _Text_H

#include <vector>
#include "phoboz/media_db.h"

// Hidden
struct TextLine;

class Text {
public:
    Text(const char *fontname, MediaDB *media, void *data = 0,
         const Sprite *icon_spr = 0, int icon_index = 0);

    ~Text();

    void set_icon(const Sprite *icon_spr, int icon_index);
    void set_data(void *data) { m_data = data; }

    bool add_line(const char *str);
    bool replace_line(const char *str, int line_no = 0);
    bool replace_line(const char *str, Color &color, int line_no = 0);
    bool add_text(const char *str);

    int get_width() const;
    int get_height() const;
    void* get_data() const { return m_data; }

    void draw(Surface *dest, int x, int y,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    TextLine* new_line(const char *str);

    static bool m_initialized;
    MediaDB *m_media;
    void *m_data;
    Font *m_font;
    Color m_color;
    Sprite *m_icon_spr;
    int m_icon_index;
    std::vector<TextLine*> m_lines;
};

#endif

