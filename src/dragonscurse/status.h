#ifndef _Status_H
#define _Status_H

#include <vector>
#include <list>
#include "item.h"

class Arm;
class Shield;
class Armour;
class Collectable;
class Player;

class Status {
public:
    Status()
        : m_arm(0),
          m_shield(0),
          m_armour(0),
          m_gold(34),
          m_shape(0) { update(); }

    void aquire_item(Item *item) { m_items.push_back(item); }
    Item* check_item(const char *name);
    void remove_item(Item *item) { m_items.remove(item); }

    bool equip_item(const char *name);
    bool equip_item(Item *item);

    void aquire_collectable(Collectable *collectable);

    void item_list(std::vector<Item*> &list, Item::ItemType type);

    bool pay_gold(int ammount);

    Item* get_equiped_item(Item::ItemType type) const;

    void aquire_shape(Player *player);

    int get_cp() const { return m_cp; }
    int get_gold() const { return m_gold; }

    void show() const;

private:
    void update();

    std::list<Item*> m_items;
    Arm *m_arm;
    Shield *m_shield;
    Armour *m_armour;

    std::list<Player*> m_shapes;
    Player *m_shape;

    int m_ap;
    int m_dp;
    int m_cp;
    int m_gold;
};

#endif

