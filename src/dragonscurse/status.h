#ifndef _Status_H
#define _Status_H

#include <vector>
#include <list>

class Item;
class Arm;
class Shield;
class Armour;
class Collectable;

class Status {
public:
    Status()
        : m_arm(0),
          m_shield(0),
          m_armour(0),
          m_gold(34) { update(); }

    void aquire_item(Item *item) { m_items.push_back(item); }
    Item* check_item(const char *name);
    void remove_item(Item *item) { m_items.remove(item); }

    bool equip_item(const char *name);
    bool equip_item(Item *item);

    void aquire_collectable(Collectable *collectable);

    void shield_list(std::vector<Shield*> &list);

    bool pay_gold(int ammount);

    Arm* get_equiped_arm() const { return m_arm; }
    Shield* get_equiped_shield() const { return m_shield; }
    Armour* get_equiped_armour() const { return m_armour; }
    int get_cp() const { return m_cp; }
    int get_gold() const { return m_gold; }

    void show() const;

private:
    void update();

    std::list<Item*> m_items;
    Arm *m_arm;
    Shield *m_shield;
    Armour *m_armour;

    int m_ap;
    int m_dp;
    int m_cp;
    int m_gold;
};

#endif

