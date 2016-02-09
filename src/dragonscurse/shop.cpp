#include "phoboz/ctrl.h"
#include "object_factory.h"
#include "area.h"
#include "item.h"
#include "shop.h"

Shop::Shop(const char *name, MediaDB *media, WorldDB *db,
           const char *src, int sx, int sy)
    : Room("shop.png", "Wonderfull_18", media, src, sx, sy, 94, 240),
      m_name(name),
      m_db(db)
{
    m_text->add_text("Shoping\n please");
    m_price_label = new Text("Wonderfull_18", media);
    m_price_label->add_line("Price");
    m_price_text = new Text("Wonderfull_18", media);
    m_price_text->add_line("000000 Gold");
    m_menu = new Menu("Wonderfull_18", "icons.png", 0, media);
    m_menu->set_spacing(80);

    for (int i = 1; i <= 4; i++) {
        ObjectInfo info;
        if (db->get_object_info(&info, i, m_name.c_str())) {
            if (info.object_type == Object::TypeItem) {
                Object *object =
                    ObjectFactory::create_item(info.data.material.name,
                                               m_media);
                if (object && object->get_loaded()) {
                    Item *item = (Item *) object;
                    item->set_world_key(info.key);

                    Status *status = m_db->get_status();
                    if (item->get_attribute("req_cp") <= status->get_cp()) {
                        m_menu->add_option(item->get_name(),
                                           item,
                                           item->get_sprite(),
                                           item->get_attribute("still"));
                        if (i == 1) {
                            static char str[12];
                            Color color;
                            sprintf(str, "%06d Gold",
                                    item->get_attribute("price"));
                            if (status->get_gold() <
                                item->get_attribute("price")) {
                                color.set_named(Color::Red);
                            }
                            else {
                                color.set_named(Color::White);
                            }
                            m_price_text->replace_line(str, color);
                        }
                    }
                    else {
                        m_menu->add_option("", 0, item->get_sprite(),
                                           item->get_attribute("unknown"));
                    }
                }
            }
        }
        else {
            m_menu->add_option("Sold out!");
        }
    }

    m_menu->add_option("Exit");
}

Area* Shop::move(int key)
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
        if (m_menu->get_option() == 4) {
            m_media->play_sound("select.wav");
            area = new Area(m_src.c_str(), m_sx, m_sy);
        }
        else {
            Item *item = (Item *) m_menu->get_data();
            if (item) {
                Status *status = m_db->get_status();
                if (status->pay_gold(item->get_attribute("price"))) {
                    m_menu->replace_option("Sold out!");
                    item->aquire(m_db);
                    status->aquire_item(item);
                    m_media->play_sound("select.wav");
                }
                else {
                    m_media->play_sound("reject.wav");
                    rejected = true;
                }
            }
            else {
                m_media->play_sound("reject.wav");
                rejected = true;
            }
        }
    }

    if (data) {
        Item *item = (Item *) data;
        static char str[12];
        Color color;
        sprintf(str, "%06d Gold", item->get_attribute("price"));
        Status *status = m_db->get_status();
        if (status->get_gold() < item->get_attribute("price")) {
            color.set_named(Color::Red);
        }
        else {
            color.set_named(Color::White);
        }
        m_price_text->replace_line(str, color);
    }
    else if (!rejected) {
        static char str[12];
        Color color(Color::White);
        sprintf(str, "000000 Gold");
        m_price_text->replace_line(str, color);
    }

    return area;
}

void Shop::draw(Surface *dest, int x, int y,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    Room::draw(dest, x, y, clip_x, clip_y, clip_w, clip_h);
    m_price_label->draw(dest, x + 48, y + 342, clip_x, clip_y, clip_w, clip_h);
    m_price_text->draw(dest, x + 100, y + 380, clip_x, clip_y, clip_w, clip_h);
    m_menu->draw(dest, x + 302, y + 40, clip_x, clip_y, clip_w, clip_h);
}

