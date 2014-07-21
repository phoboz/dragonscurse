#include "shield.h"
#include "shield_list.h"

ShieldList::ShieldList(MediaDB *media, Status *status)
    : SubMenu(media, status)
{
    std::vector<Shield*> list;

    status->shield_list(list);

    for (int i = 0; i < list.size(); i++) {
        Shield *shield = list[i];
        m_menu->add_option(shield->get_filename(), shield);
    }
}

