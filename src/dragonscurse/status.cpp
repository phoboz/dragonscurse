#include <iostream>
#include "item.h"
#include "sword.h"
#include "shield.h"
#include "armour.h"
#include "status.h"

void Status::update()
{
    ap = 0;
    dp = 0;
    cp = 0;

    if (m_sword) {
        ap += m_sword->get_attribute("ap");
    }

    if (m_shield) {
        dp += m_shield->get_attribute("dp");
    }

    if (m_armour) {
        dp += m_armour->get_attribute("dp");
        cp += m_armour->get_attribute("cp");
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

void Status::show() const
{

    std::cout << "Stats:" << std::endl;
    std::cout << "Attack points: " << ap << std::endl;
    std::cout << "Defence points: " << dp << std::endl;
    std::cout << "Charm points: " << cp << std::endl;
    std::cout << std::endl;

    std::cout << "Items:" << std::endl;
    for (std::list<Item*>::const_iterator it = m_items.begin();
         it != m_items.end();
         ++it) {

        Item *item = *it;
        std::cout << "Item: " << item->get_filename() << std::endl;
    }
}

