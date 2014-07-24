#include "item_list.h"

ItemList::ItemList(MediaDB *media, Status *status, Item::ItemType item_type)
    : SubMenu(media, status)
{
    std::vector<Item*> list;

    status->item_list(list, item_type);

    for (int i = 0; i < list.size(); i++) {
        Item *item = list[i];
        m_menu->add_option(item->get_name(), item);
    }
}

ItemList::~ItemList()
{
}

int ItemList::move(int key)
{
    int result = SubMenu::move(key);
    if (result > 0) {
        // TODO: Show item info
    }

    return result;
}

