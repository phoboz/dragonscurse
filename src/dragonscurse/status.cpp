#include <iostream>
#include "item.h"
#include "arm.h"
#include "shield.h"
#include "armour.h"
#include "collectable.h"
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
        if (strcmp(name, item->get_filename()) == 0) {
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
    m_shapes.push_back(player);
    m_shape = player;
    update();
}

bool Status::set_hit(int ap)
{
    bool result = false;

    int hp = ap - m_dp;
    if (hp > 0) {
        m_hp -= ap;
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
}

