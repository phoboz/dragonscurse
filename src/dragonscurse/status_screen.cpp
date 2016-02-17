#include "phoboz/media_db.h"
#include "status.h"
#include "status_screen.h"

StatusScreen::StatusScreen(Status *status, MediaDB *media)
    : m_status(status)
{
    m_ap_label = new Text("Wonderfull_18", media);
    m_ap_label->add_line("AP: ");
    m_ap_text = new Text("Wonderfull_18", media);
    m_ap_text->add_line("000");

    m_dp_label = new Text("Wonderfull_18", media);
    m_dp_label->add_line("DP: ");
    m_dp_text = new Text("Wonderfull_18", media);
    m_dp_text->add_line("000");

    m_cp_label = new Text("Wonderfull_18", media);
    m_cp_label->add_line("CP: ");
    m_cp_text = new Text("Wonderfull_18", media);
    m_cp_text->add_line("000");

    m_fire_label = new Text("Wonderfull_18", media);
    m_fire_label->add_line("Fire: ");
    m_fire_text = new Text("Wonderfull_18", media);
    m_fire_text->add_line("00");

    m_tornado_label = new Text("Wonderfull_18", media);
    m_tornado_label->add_line("Tornado: ");
    m_tornado_text = new Text("Wonderfull_18", media);
    m_tornado_text->add_line("00");

    m_arrow_label = new Text("Wonderfull_18", media);
    m_arrow_label->add_line("Arrow: ");
    m_arrow_text = new Text("Wonderfull_18", media);
    m_arrow_text->add_line("00");

    m_boomerang_label = new Text("Wonderfull_18", media);
    m_boomerang_label->add_line("Boomerang: ");
    m_boomerang_text = new Text("Wonderfull_18", media);
    m_boomerang_text->add_line("00");

    m_thunder_label = new Text("Wonderfull_18", media);
    m_thunder_label->add_line("Thunder: ");
    m_thunder_text = new Text("Wonderfull_18", media);
    m_thunder_text->add_line("00");
}

void StatusScreen::move()
{
    static char str[3];

    sprintf(str, "%03d", m_status->get_ap());
    m_ap_text->replace_line(str);

    sprintf(str, "%03d", m_status->get_dp());
    m_dp_text->replace_line(str);

    sprintf(str, "%03d", m_status->get_cp());
    m_cp_text->replace_line(str);

    sprintf(str, "%02d", m_status->get_fires());
    m_fire_text->replace_line(str);

    sprintf(str, "%02d", m_status->get_tornados());
    m_tornado_text->replace_line(str);

    sprintf(str, "%02d", m_status->get_arrows());
    m_arrow_text->replace_line(str);

    sprintf(str, "%02d", m_status->get_boomerangs());
    m_boomerang_text->replace_line(str);

    sprintf(str, "%02d", m_status->get_thunders());
    m_thunder_text->replace_line(str);
}

void StatusScreen::draw(Surface *dest, int x, int y,
                        int clip_x, int clip_y, int clip_w, int clip_h)
{
    int tx = clip_w - c_stat_dx;
    int ty = y;

    Color color(Color::BrightGreen);
    Rect rect(clip_x, clip_y, clip_w, clip_h);
    dest->fill_rect(&rect, &color);

    m_ap_label->draw(dest, tx, y, clip_x, clip_y, clip_w, clip_h);
    m_ap_text->draw(dest, tx + m_ap_label->get_width(), y,
                    clip_x, clip_y, clip_w, clip_h);
    y += m_ap_text->get_height();

    m_dp_label->draw(dest, tx, y, clip_x, clip_y, clip_w, clip_h);
    m_dp_text->draw(dest, tx + m_ap_label->get_width(), y,
                    clip_x, clip_y, clip_w, clip_h);
    y += m_dp_text->get_height();

    m_cp_label->draw(dest, tx, y, clip_x, clip_y, clip_w, clip_h);
    m_cp_text->draw(dest, tx + m_ap_label->get_width(), y,
                    clip_x, clip_y, clip_w, clip_h);
    y += m_cp_text->get_height();

    tx = clip_w - c_magic_dx;
    y = clip_h - c_magic_dy;

    m_fire_label->draw(dest, tx, y, clip_x, clip_y, clip_w, clip_h);
    m_fire_text->draw(dest, tx + m_boomerang_label->get_width(), y,
                      clip_x, clip_y, clip_w, clip_h);
    y += m_fire_text->get_height();

    m_tornado_label->draw(dest, tx, y, clip_x, clip_y, clip_w, clip_h);
    m_tornado_text->draw(dest, tx + m_boomerang_label->get_width(), y,
                         clip_x, clip_y, clip_w, clip_h);
    y += m_tornado_text->get_height();

    m_arrow_label->draw(dest, tx, y, clip_x, clip_y, clip_w, clip_h);
    m_arrow_text->draw(dest, tx + m_boomerang_label->get_width(), y,
                       clip_x, clip_y, clip_w, clip_h);
    y += m_arrow_text->get_height();

    m_boomerang_label->draw(dest, tx, y, clip_x, clip_y, clip_w, clip_h);
    m_boomerang_text->draw(dest, tx + m_boomerang_label->get_width(), y,
                           clip_x, clip_y, clip_w, clip_h);
    y += m_boomerang_text->get_height();

    m_thunder_label->draw(dest, tx, y, clip_x, clip_y, clip_w, clip_h);
    m_thunder_text->draw(dest, tx + m_boomerang_label->get_width(), y,
                         clip_x, clip_y, clip_w, clip_h);
}

