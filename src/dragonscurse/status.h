#ifndef _Status_H
#define _Status_H

#include <list>

class Item;
class Sword;
class Shield;
class Armour;
class Collectable;

class Status {
public:
    Status()
        : m_sword(0),
          m_shield(0),
          m_armour(0),
          m_gold(0) { update(); }

    void aquire_item(Item *item) { m_items.push_back(item); }
    Item* check_item(const char *name);
    void remove_item(Item *item) { m_items.remove(item); }

    bool equip_item(const char *name);

    void aquire_collectable(Collectable *collectable);

    int get_cp() const { return m_cp; }
    int get_gold() const { return m_gold; }

    void show() const;

private:
    void update();

    std::list<Item*> m_items;
    Sword *m_sword;
    Shield *m_shield;
    Armour *m_armour;

    int m_ap;
    int m_dp;
    int m_cp;
    int m_gold;
};

#endif

