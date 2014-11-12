#include <iostream>
#include <string.h>
#include "item.h"
#include "arm.h"
#include "shield.h"
#include "armour.h"
#include "collectable.h"
#include "heart.h"
#include "store_restore.h"
#include "object_factory.h"
#include "status.h"

void Status::update()
{
    if (m_shape) {
        m_ap = m_shape->get_attribute("ap");
        m_dp = m_shape->get_attribute("dp");
        m_cp = m_shape->get_attribute("cp");
    }
    else {
        m_ap = 0;
        m_dp = 0;
        m_cp = 0;
    }

    if (m_arm) {
        m_ap += m_arm->get_attribute("ap");
    }

    if (m_shield) {
        m_dp += m_shield->get_attribute("dp");
    }

    if (m_armour) {
        m_dp += m_armour->get_attribute("dp");
        m_cp += m_armour->get_attribute("cp");
    }
}

Item* Status::check_item(const char *name)
{
    Item *result = 0;

    for (std::list<Item*>::iterator it = m_items.begin();
         it != m_items.end();
         ++it) {

        Item *item = *it;
        if (item && strcmp(name, item->get_filename()) == 0) {
            result = item;
            break;
        }
    }

    return result;
}

bool Status::equip_item(const char *name)
{
    bool result = false;

    Item *item = check_item(name);
    if (item) {
        result = equip_item(item);
    }

    return result;
}

bool Status::equip_item(Item *item)
{
    bool result = false;

    if (item) {
        switch(item->get_item_type()) {
            case Item::TypeArm:
                m_arm = (Arm *) item;
                update();
                result = true;
                break;

            case Item::TypeShield:
                m_shield = (Shield *) item;
                update();
                result = true;
                break;

            case Item::TypeArmour:
                m_armour = (Armour *) item;
                update();
                result = true;
                break;

            default:
                break;
        }
    }

    return result;
}

void Status::item_list(std::vector<Item*> &list, Item::ItemType type)
{
    for (std::list<Item*>::iterator it = m_items.begin();
         it != m_items.end();
         ++it) {

        Item *item = *it;
        if (item->get_item_type() == type) {
            list.push_back((Shield *) item);
        }
    }
}

void Status::aquire_collectable(Collectable *collectable)
{
    switch (collectable->get_collectable_type()) {
        case Collectable::TypeGold:
            m_gold += collectable->get_value();
            break;

        case Collectable::TypeHeartContainer:
            add_hearts(1/*collectable->get_value()*/);
            break;

        default:
            break;
    }
}

bool Status::pay_gold(int ammount)
{
    bool result = false;

    if (ammount <= m_gold) {
        m_gold -= ammount;
        result = true;
    }

    return result;
}

Item* Status::get_equiped_item(Item::ItemType type) const
{
    Item *item = 0;

    switch(type) {
        case Item::TypeArm:
            item = (Item *) m_arm;
            break;

        case Item::TypeShield:
            item = (Item *) m_shield;
            break;

        case Item::TypeArmour:
            item = (Item *) m_armour;

        default:
            break;
    }

    return item;
}

void Status::aquire_shape(Player *player)
{
    bool found = false;
    int num_shapes = m_shapes.size();

    for (int i = 0; i < num_shapes; i++) {
        if (m_shapes[i]->get_filename() == player->get_filename()) {
            found = true;
            break;
        }
    }

    if (!found) {
        m_shapes.push_back(player);
    }

    m_shape = player;
    update();
}

void Status::add_hearts(int num_hearts)
{
    int i = num_hearts + 1;
    while (--i && m_hearts < c_max_hearts) {
        m_hearts++;
        m_max_hp += Heart::get_hp_per_heart();
        m_hp += Heart::get_hp_per_heart();
    }
}

bool Status::set_hit(int ap)
{
    bool result = false;

    int hp = ap - m_dp;
    if (hp > 0) {
        m_hp -= hp;
        if (m_hp <= 0) {
            result = true;
        }
    }

    return result;
}

void Status::show() const
{

    std::cout << "Status:" << std::endl;
    std::cout << "AP: " << "\t" << m_ap << std::endl;
    std::cout << "DP: " << "\t" << m_dp << std::endl;
    std::cout << "CP: " << "\t" << m_cp << std::endl;
    std::cout << "Gold: " << "\t" << m_gold << std::endl;
    std::cout << "HP: " << "\t" << m_hp << std::endl;
    std::cout << std::endl;

    std::cout << "Items:" << std::endl;
    for (std::list<Item*>::const_iterator it = m_items.begin();
         it != m_items.end();
         ++it) {

        Item *item = *it;
        std::cout << "Item: " << item->get_name();
        if (item == get_equiped_item(Item::TypeArm)) {
            std::cout << " (equiped arm)";
        }
        else if (item == get_equiped_item(Item::TypeShield)) {
            std::cout << " (equiped shield)";
        }
        else if (item == get_equiped_item(Item::TypeArmour)) {
            std::cout << " (equiped armour)";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Shapes:" << std::endl;
    int num_shapes = m_shapes.size();
    for (int i = 0; i < num_shapes; i++) {
        Player *shape = m_shapes[i];
        std::cout << "Shape: " << shape->get_name();
        if (shape == m_shape) {
            std::cout << " (current shape)";
        }
        std::cout << std::endl;
    }
}

bool Status::write(std::ofstream &f)
{
    bool result = true;

    StoreRestore::write_integer(f, m_hearts);
    StoreRestore::write_integer(f, m_gold);

    StoreRestore::write_integer(f, m_items.size());
    for (std::list<Item*>::iterator it = m_items.begin();
         it != m_items.end();
         ++it) {

        Item *item = *it;
        if (item) {
            bool is_equiped = false;

            if (item == m_arm || item == m_shield || item == m_armour) {
                is_equiped = true;
            }
            StoreRestore::write_varchar(f, item->get_filename());
            StoreRestore::write_boolean(f, is_equiped);
        }
    }

    int num_shapes = m_shapes.size();
    StoreRestore::write_integer(f, num_shapes);
    for (int i = 0; i < num_shapes; i++) {

        Player *player = m_shapes[i];
        if (player) {
            bool has_shape = false;

            if (player == m_shape) {
                has_shape = true;
            }
            StoreRestore::write_varchar(f, player->get_filename());
            StoreRestore::write_boolean(f, has_shape);
        }
    }

    return result;
}

bool Status::read(std::ifstream &f, MediaDB *media)
{
    bool result = true;

    add_hearts(StoreRestore::read_integer(f));

    m_gold = StoreRestore::read_integer(f);

    int num_items = StoreRestore::read_integer(f);
    for (int i = 0; i < num_items; i++) {
        char *name = StoreRestore::read_varchar(f);
        aquire_item((Item *) ObjectFactory::create_object(name, media, "Item"));
        if (StoreRestore::read_boolean(f)) {
            equip_item(name);
        }
        delete name;
    }

    int num_shapes = StoreRestore::read_integer(f);
    for (int i = 0; i < num_shapes; i++) {
        char *name = StoreRestore::read_varchar(f);
        Player *shape = (Player *) ObjectFactory::create_object(name, media,
                                                                "Player");
        m_shapes.push_back(shape);
        if (StoreRestore::read_boolean(f)) {
            m_shape = shape;
        }
        delete name;
    }

    show();

    return result;
}

