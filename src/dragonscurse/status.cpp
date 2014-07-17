#include <iostream>
#include "item.h"
#include "sword.h"
#include "shield.h"
#include "armour.h"
#include "collectable.h"
#include "status.h"

void Status::update()
{
    m_ap = 0;
    m_dp = 0;
    m_cp = 0;

    if (m_sword) {
        m_ap += m_sword->get_attribute("ap");
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
        switch(item->get_item_type()) {
            case Item::TypeSword:
                m_sword = (Sword *) item;
                update();
                break;

            case Item::TypeShield:
                m_shield = (Shield *) item;
                update();
                break;

            case Item::TypeArmour:
                m_armour = (Armour *) item;
                update();
                break;

            default:
                break;
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

void Status::show() const
{

    std::cout << "Status:" << std::endl;
    std::cout << "AP: " << "\t" << m_ap << std::endl;
    std::cout << "DP: " << "\t" << m_dp << std::endl;
    std::cout << "DP: " << "\t" << m_cp << std::endl;
    std::cout << "Gold: " << "\t" << m_gold << std::endl;
    std::cout << std::endl;

    std::cout << "Items:" << std::endl;
    for (std::list<Item*>::const_iterator it = m_items.begin();
         it != m_items.end();
         ++it) {

        Item *item = *it;
        std::cout << "Item: " << item->get_filename() << std::endl;
    }
}

