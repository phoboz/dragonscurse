#ifndef _Status_H
#define _Status_H

#include <list>

class Item;

class Status {
public:
    void aquire_item(Item *item) { m_items.push_back(item); }
    Item* check_item(const char *name);
    void remove_item(Item *item) { m_items.remove(item); }

    void list_items() const;

private:
    std::list<Item*> m_items;
};

#endif

