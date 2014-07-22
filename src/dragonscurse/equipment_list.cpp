#include <string>
#include "equipment_list.h"

EquipmentList::EquipmentList(MediaDB *media, Status *status,
                             Item::ItemType item_type, int spr_index)
    : SubMenu(media, status),
      m_spr_index(spr_index),
      m_curr_eq(0)
{
    std::vector<Item*> list;

    status->item_list(list, item_type);

    m_spr = media->get_sprite("icons_small.png");
    Item *eq_item = status->get_equiped_item(item_type);

    for (int i = 0; i < list.size(); i++) {
        Item *item = list[i];
        std::string fn(item->get_filename());
        int lastindex = fn.find_last_of(".");
        std::string rawname = fn.substr(0, lastindex);

        if (item == eq_item) {
            m_menu->add_option(rawname.c_str(), item, m_spr, m_spr_index);
            m_curr_eq = i + 1;
        }
        else {
            m_menu->add_option(rawname.c_str(), item);
        }
    }
}

EquipmentList::~EquipmentList()
{
    m_media->leave_sprite(m_spr);
}

int EquipmentList::move(int key)
{
    int result = SubMenu::move(key);
    if (result > 0) {
        Item *item = (Item *) m_menu->get_data();
        if (m_status->equip_item(item)) {
            if (m_curr_eq) {
                m_menu->set_icon(m_curr_eq, 0, 0);
            }
            m_menu->set_icon(m_spr, m_spr_index);
            m_curr_eq = m_menu->get_option();
        }
    }

    return result;
}

