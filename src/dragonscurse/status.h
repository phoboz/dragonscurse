#ifndef _Status_H
#define _Status_H

#include <list>

class Item;
class Sword;
class Shield;
class Armour;

class Status {
public:
    Status()
        : m_sword(0),
          m_shield(0),
          m_armour(0) { update(); }

    void aquire_item(Item *item) { m_items.push_back(item); }
    Item* check_item(const char *name);
    void remove_item(Item *item) { m_items.remove(item); }

    bool equip_item(const char *name);

    int get_cp() const { return cp; }

    void show() const;

private:
    void update();

    std::list<Item*> m_items;
    Sword *m_sword;
    Shield *m_shield;
    Armour *m_armour;

    int ap;
    int dp;
    int cp;
};

#endif

