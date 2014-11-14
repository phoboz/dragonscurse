#include <string.h>
#include <string>
#include "statusbar.h"

int Statusbar::c_height = 40;

Statusbar::Statusbar(Status *status, MediaDB *media)
    : m_status(status), m_media(media)
{
    int max_hearts = status->get_max_hearts();
    m_hearts = new Heart*[max_hearts];
    for (int i = 0; i < max_hearts; i++) {
        m_hearts[i] = new Heart(media);
    }

    m_potion_sprite = media->get_sprite("potion.png");
    m_potions_text = new Text("Wonderfull_18", media);
    m_potions_text->add_line("0");

    m_gold_label = new Text("Wonderfull_18", media);
    m_gold_label->add_line("Gold");

    m_gold_text = new Text("Wonderfull_18", media);
    m_gold_text->add_line("000000");
}

Statusbar::~Statusbar()
{
    for (int i = 0; i < m_status->get_max_hearts(); i++) {
        delete m_hearts[i];
    }

    m_media->leave_sprite(m_potion_sprite);
}

void Statusbar::draw(Surface *surface, int screen_width, int screen_height)
{
    Rect top_rect(0, 0, screen_width, c_height - 2);
    Color top_color(Color::Grey);
    surface->fill_rect(&top_rect, &top_color);

    Rect bottom_rect(0, c_height - 2, screen_width, 2);
    Color bottom_color(Color::DarkGrey);
    surface->fill_rect(&bottom_rect, &bottom_color);

    int w = m_hearts[0]->get_width();
    int num_full = m_status->get_hp() / Heart::get_hp_per_heart();
    int partial = m_status->get_hp() % Heart::get_hp_per_heart();
    int x_pos = 4;

    for (int i = 0; i < m_status->get_hearts(); i++) {
        if (i < num_full) {
            m_hearts[i]->set_full();
        }
        else if (i == num_full && partial > 0) {
            m_hearts[i]->set_hp(partial);
        }
        else {
            m_hearts[i]->set_empty();
        }
        m_hearts[i]->draw(surface, x_pos, 4,
                          0, 0, screen_width, screen_height);
        x_pos += w + 4;
    }

    m_potion_sprite->draw(surface, screen_width - 240, 4,
                          0, 0, 0, screen_width, screen_height);

    static char str[6];
    sprintf(str, "%02d", m_status->get_potions());
    m_potions_text->replace_line(str);
    m_potions_text->draw(surface, screen_width - 200, c_height - 20,
                         0, 0, screen_width, screen_height);

    sprintf(str, "%06d", m_status->get_gold());
    m_gold_text->replace_line(str);
    m_gold_label->draw(surface, screen_width - 120, 0,
                       0, 0, screen_width, screen_height);
    m_gold_text->draw(surface, screen_width - 80, c_height - 20,
                      0, 0, screen_width, screen_height);
}

