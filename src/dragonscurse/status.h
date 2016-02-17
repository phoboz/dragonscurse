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
          m_potions(0),
          m_stones(0),
          m_fires(0),
          m_tornados(0),
          m_arrows(0),
          m_boomerangs(0),
          m_thunders(0),
          m_break_rock(false),
          m_create_rock(false),
          m_arm(0),
          m_shield(0),
          m_armour(0),
          m_gold(0),
          m_hp(0),
          m_max_hp(0) { update(); }

    void aquire(Material *material);
    void aquire_item(Item *item) { m_items.push_back(item); }
    Item* check_item(const char *name);
    void remove_item(Item *item) { m_items.remove(item); }

    bool equip_item(const char *name);
    bool equip_item(Item *item);

    void aquire_collectable(Collectable *collectable);

    void item_list(std::vector<Item*> &list, Item::ItemType type);

    bool pay_gold(int ammount);

    Item* get_equiped_item(Item::ItemType type) const;
    int get_potions() const { return m_potions; }
    int get_cure_price() const { return 10 * m_hearts; }

    void aquire_shape(Player *player);

    void add_hearts(int num);
    void add_potions(int num);
    void add_stones(int num) { m_stones += num; }
    void add_fires(int num) { m_fires += num; }
    void add_tornados(int num) { m_tornados += num; }
    void add_arrows(int num) { m_arrows += num; }
    void add_boomerangs(int num) { m_boomerangs += num; }
    void add_thunders(int num) { m_thunders += num; }
    void add_break_rock() { m_break_rock = true; }
    void add_create_rock() { m_create_rock = true; }

    void cure(int value = 0);

    bool set_hit(int ap);

    bool use_potion();

    static int get_max_hearts() { return c_max_hearts; }
    int get_hearts() const { return m_hearts; }
    bool get_break_rock() const { return m_break_rock; }
    bool get_create_rock() const { return m_create_rock; }
    int get_ap() const { return m_ap; }
    int get_dp() const { return m_dp; }
    int get_cp() const { return m_cp; }
    int get_fires() const { return m_fires; }
    int get_tornados() const { return m_tornados; }
    int get_arrows() const { return m_arrows; }
    int get_boomerangs() const { return m_boomerangs; }
    int get_thunders() const { return m_thunders; }
    int get_gold() const { return m_gold; }
    int get_hp() const { return m_hp; }
    Player* get_shape() const { return m_shape; }

    void update();
    void show() const;
    bool write(std::ofstream &f);
    bool read(std::ifstream &f, MediaDB *media);

private:
    static const int c_max_hearts = 8;
    static const int c_max_potions = 3;

    std::list<Item*> m_items;
    Arm *m_arm;
    Shield *m_shield;
    Armour *m_armour;

    std::vector<Player*> m_shapes;
    Player *m_shape;

    int m_hearts;
    int m_potions;
    int m_stones;
    int m_fires;
    int m_tornados;
    int m_arrows;
    int m_boomerangs;
    int m_thunders;
    bool m_break_rock;
    bool m_create_rock;

    int m_ap;
    int m_dp;
    int m_cp;
    int m_gold;
    int m_hp;
    int m_max_hp;
};

#endif

