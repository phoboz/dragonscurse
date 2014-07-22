#include "shield.h"
#include "shield_list.h"

ShieldList::ShieldList(MediaDB *media, Status *status)
    : SubMenu(media, status),
      m_curr_eq(0)
{
    std::vector<Shield*> list;

    status->shield_list(list);

    m_spr = media->get_sprite("icons_small.png");
    Shield *eq_shield = status->get_equiped_shield();

    for (int i = 0; i < list.size(); i++) {
        Shield *shield = list[i];
        if (shield == eq_shield) {
            m_menu->add_option(shield->get_filename(), shield, m_spr, 1);
            m_curr_eq = i + 1;
        }
        else {
            m_menu->add_option(shield->get_filename(), shield);
        }
    }
}

ShieldList::~ShieldList()
{
    m_media->leave_sprite(m_spr);
}

int ShieldList::move(int key)
{
    int result = SubMenu::move(key);
    if (result > 0) {
        Item *item = (Item *) m_menu->get_data();
        if (m_status->equip_item(item)) {
            if (m_curr_eq) {
                m_menu->set_icon(m_curr_eq, 0, 0);
            }
            m_menu->set_icon(m_spr, 1);
            m_curr_eq = m_menu->get_option();
        }
    }

    return result;
}

