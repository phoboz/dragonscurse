#include "monster.h"

Monster::Monster(const char *fn, int x, int y, Direction dir)
    : Actor(Object::TypeEnemy, x, y, dir)
{
    load(fn);
    m_curr_hp = get_attribute("hp");
}

bool Monster::set_hit(Object *object)
{
    bool result = false;

    if (m_action != Hit) {
        Actor::set_hit(object);

        // Reduce hp
        // TODO: Get attackers attack power
        m_curr_hp--;
        if (m_curr_hp <= 0) {
            set_invisible(true);
            m_action = Perish;
        }

        result = true;
    }

    return result;
}

void Monster::move(Map *map)
{
    if (m_action == Perish) {
        if (m_perish_timer.expired(get_attribute("perish_time"))) {
            m_action = Perished;
        }
    }
}

