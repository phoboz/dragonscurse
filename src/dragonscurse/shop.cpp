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
    m_menu = new Menu("Wonderfull_18", "icons.png", 0, media);
    m_menu->set_spacing(80);

    for (int i = 1; i <= 4; i++) {
        ObjectInfo info;
        if (db->get_object_info(&info, i, m_name.c_str())) {
            if (info.object_type == Object::TypeItem) {
                Object *object =
                    ObjectFactory::create_object(info.data.item.name,
                                                 m_media, "Item");
                if (object && object->get_loaded()) {
                    Item *item = (Item *) object;
                    item->set_world_key(info.key);

                    if (item->get_attribute("req_cp") <= db->get_cp()) {
                        std::string fn(item->get_filename());
                        int lastindex = fn.find_last_of("."); 
                        std::string rawname = fn.substr(0, lastindex); 
                        m_menu->add_option(rawname.c_str(),
                                           item->get_sprite(),
                                           item->get_attribute("still"));
                    }
                    else {
                        m_menu->add_option("", item->get_sprite(),
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
    int input = get_input_keydown(key);
    if (input & PRESS_DOWN) {
        m_menu->advance_pointer(Menu::DirectionDown);
        m_media->play_sound("advance.wav");
    }
    else if (input & PRESS_UP) {
        m_menu->advance_pointer(Menu::DirectionUp);
        m_media->play_sound("advance.wav");
    }
    else if (input & PRESS_ENTER) {
        if (m_menu->get_option() == 4) {
            m_media->play_sound("select.wav");
            return new Area(m_src.c_str(), m_sx, m_sy);
        }
        else {
            m_media->play_sound("reject.wav");
        }
    }
    else if (input & PRESS_ESC) {
        return new Area(m_src.c_str(), m_sx, m_sy);
    }

    return 0;
}

void Shop::draw(SDL_Surface *dest, int x, int y,
                  int clip_x, int clip_y, int clip_w, int clip_h)
{
    Room::draw(dest, x, y, clip_x, clip_y, clip_w, clip_h);
    m_menu->draw(dest, x + 302, y + 40, clip_x, clip_y, clip_w, clip_h);
}

