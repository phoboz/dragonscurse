#ifndef _Status_H
#define _Status_H

#include <fstream>
#include <vector>
#include <list>
#include "phoboz/media_db.h"
#include "item.h"

class Arm;
class Shield;
class Armour;
class Collectable;
class Player;

class Status {
public:
    Status()
        : m_shape(0),
          m_hearts(0),
          m_arm(0),
          m_shield(0),
          m_armour(0),
          m_gold(0),
          m_hp(0),
          m_max_hp(0) { update(); }

    void aquire_item(Item *item) { m_items.push_back(item); }
    Item* check_item(const char *name);
    void remove_item(Item *item) { m_items.remove(item); }

    bool equip_item(const char *name);
    bool equip_item(Item *item);

    void aquire_collectable(Collectable *collectable);

    void item_list(std::vector<Item*> &list, Item::ItemType type);

    bool pay_gold(int ammount);

    Item* get_equiped_item(Item::ItemType type) const;
    int get_cure_price() const { return 10 * m_hearts; }

    void aquire_shape(Player *player);

    void add_hearts(int num_hearts);
    void cure() { m_hp = m_max_hp; }
    bool set_hit(int ap);

    static int get_max_hearts() { return c_max_hearts; }
    int get_hearts() const { return m_hearts; }
    int get_ap() const { return m_ap; }
    int get_dp() const { return m_dp; }
    int get_cp() const { return m_cp; }
    int get_gold() const { return m_gold; }
    int get_hp() const { return m_hp; }

    void show() const;
    bool write(std::ofstream &f);
    bool read(std::ifstream &f, MediaDB *media);

private:
    static const int c_max_hearts = 8;

    void update();

    std::list<Item*> m_items;
    Arm *m_arm;
    Shield *m_shield;
    Armour *m_armour;

    std::vector<Player*> m_shapes;
    Player *m_shape;

    int m_hearts;

    int m_ap;
    int m_dp;
    int m_cp;
    int m_gold;
    int m_hp;
    int m_max_hp;
};

#endif

