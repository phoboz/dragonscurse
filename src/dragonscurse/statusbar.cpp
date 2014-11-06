#include <string.h>
#include <string>
#include "SDL.h"
#include "statusbar.h"

int Statusbar::c_height = 40;

Statusbar::Statusbar(Status *status, MediaDB *media)
    : m_status(status), m_media(media)
{
    for (int i = 0; i < c_max_hearts; i++) {
        m_hearts[i] = new Heart(media);
    }

    m_gold_label = new Text("Wonderfull_18", media);
    m_gold_label->add_line("Gold");

    m_gold_text = new Text("Wonderfull_18", media);
    m_gold_text->add_line("000000");
}

Statusbar::~Statusbar()
{
    for (int i = 0; i < c_max_hearts; i++) {
        delete m_hearts[i];
    }
}

void Statusbar::draw(SDL_Surface *surface, int screen_width, int screen_height)
{
    SDL_Rect dest_rect;

    dest_rect.x = 0;
    dest_rect.y = 0;
    dest_rect.w = screen_width;
    dest_rect.h = c_height - 2;
    SDL_FillRect(surface, &dest_rect, 0x54545454);

    dest_rect.x = 0;
    dest_rect.y = c_height - 2;
    dest_rect.w = screen_width;
    dest_rect.h = 2;
    SDL_FillRect(surface, &dest_rect, 0x33333333);

    float hp_per_heart = m_status->get_max_hp() / c_max_hearts;
    int num_hearts = m_status->get_max_hp() / hp_per_heart;
    int full_hearts = m_status->get_hp() / hp_per_heart;
    float hp_left = m_status->get_hp() - full_hearts * hp_per_heart;
    float q_left = hp_left / hp_per_heart;
    int percentage_left = q_left * 100;

    for (int i = 0; i < num_hearts; i++) {
        int w = m_hearts[i]->get_width();
        if (i < full_hearts) {
            m_hearts[i]->set_content_percent(100);
        }
        else if (i == full_hearts && percentage_left) {
            m_hearts[i]->set_content_percent(percentage_left);
        }
        else {
            m_hearts[i]->set_content_percent(0);
        }
        m_hearts[i]->draw(surface, 4 + i * (w + 4), 4,
                          0, 0, screen_width, screen_height);
    }

    static char str[6];
    sprintf(str, "%06d", m_status->get_gold());
    m_gold_text->replace_line(str);
    m_gold_label->draw(surface, screen_width - 120, 0,
                       0, 0, screen_width, screen_height);
    m_gold_text->draw(surface, screen_width - 80, c_height - 20,
                      0, 0, screen_width, screen_height);
}

