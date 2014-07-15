#include <iostream>
#include "item.h"
#include "status.h"

Item* Status::check_item(const char *name)
{
    Item *result = 0;

    for (std::list<Item*>::iterator it = m_items.begin();
         it != m_items.end();
         ++it) {

        Item *item = *it;
        if (strcmp(name, item->get_filename()) == 0) {
            result = item;
            break;
        }
    }

    return result;
}

void Status::list_items() const
{

    for (std::list<Item*>::const_iterator it = m_items.begin();
         it != m_items.end();
         ++it) {

        Item *item = *it;
        std::cout << "Item: " << item->get_filename() << std::endl;
    }
}

