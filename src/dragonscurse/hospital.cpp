#include "phoboz/ctrl.h"
#include "object_factory.h"
#include "area.h"
#include "hospital.h"

Hospital::Hospital(MediaDB *media, WorldDB *db, const char *src, int sx, int sy)
    : Room("hospital.png", "Wonderfull_18", media, src, sx, sy, 94, 240),
      m_db(db)
{
    m_spr = media->get_sprite("icons.png");
    m_text->add_text("Next\n please");
    m_price_label = new Text("Wonderfull_18", media);
    m_price_label->add_line("Price");
    m_price_text = new Text("Wonderfull_18", media);
    m_price_text->add_line("000000 Gold");
    m_menu = new Menu("Wonderfull_18", "icons.png", 0, media);
    m_menu->set_spacing(80);

    m_menu->add_option("Cure", (void *) 1, m_spr, 12);
    Status *status = m_db->get_status();
    static char str[12];
    sprintf(str, "%06d Gold", status->get_cure_price());
    m_price_text->replace_line(str);
    if (status->get_gold() < status->get_cure_price()) {
        m_price_text->set_color(Text::ColorRed);
    }
    else {
        m_price_text->set_color(Text::ColorWhite);
    }

    m_menu->add_option("Exit", (void *) 0, 0, 0);
}

Area* Hospital::move(int key)
{
    Area *area = 0;
    void *data = 0;
    bool rejected = false;

    int input = get_input_keydown(key);
    if (input & PRESS_DOWN) {
        data = m_menu->advance_pointer(Menu::DirectionDown);
        m_media->play_sound("advance.wav");
    }
    else if (input & PRESS_UP) {
        data = m_menu->advance_pointer(Menu::DirectionUp);
        m_media->play_sound("advance.wav");
    }
    else if (input & PRESS_ENTER) {
        if (m_menu->get_option() == 1) {
            m_media->play_sound("select.wav");
            area = new Area(m_src.c_str(), m_sx, m_sy);
        }
        else {
            Status *status = m_db->get_status();
            if (status->pay_gold(status->get_cure_price())) {
                status->cure();
                m_media->play_sound("select.wav");
            }
            else {
                m_media->play_sound("reject.wav");
                rejected = true;
            }
        }
    }

    if (data) {
        Status *status = m_db->get_status();
        static char str[12];
        sprintf(str, "%06d Gold", status->get_cure_price());
        m_price_text->replace_line(str);

        if (status->get_gold() < status->get_cure_price()) {
            m_price_text->set_color(Text::ColorRed);
        }
        else {
            m_price_text->set_color(Text::ColorWhite);
        }
    }
    else if (!rejected) {
        Status *status = m_db->get_status();
        if (status->get_gold() < status->get_cure_price()) {
            m_price_text->set_color(Text::ColorRed);
        }
        else {
            m_price_text->set_color(Text::ColorWhite);
        }
    }

    return area;
}

void Hospital::draw(SDL_Surface *dest, int x, int y,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    Room::draw(dest, x, y, clip_x, clip_y, clip_w, clip_h);
    m_price_label->draw(dest, x + 48, y + 342, clip_x, clip_y, clip_w, clip_h);
    m_price_text->draw(dest, x + 100, y + 380, clip_x, clip_y, clip_w, clip_h);
    m_menu->draw(dest, x + 302, y + 40, clip_x, clip_y, clip_w, clip_h);
}

