#include "monster.h"

Monster::Monster(const char *fn, int x, int y, Direction dir)
    : Actor(Object::TypeEnemy, x, y, dir)
{
    load(fn);
    m_curr_hp = get_attribute("hp");
    set_still();
}

bool Monster::set_hit(Object *object)
{
    bool result = false;

    if (m_hit == HitNone) {
        Actor::set_hit(object);

        // Reduce hp
        // TODO: Get attackers attack power
        m_curr_hp--;
        if (m_curr_hp <= 0) {
            set_invisible(true);
            m_hit = HitPerish;
        }

        result = true;
    }

    return result;
}

void Monster::move(Map *map)
{
    if (m_hit == HitPerish) {
        if (m_perish_timer.expired(get_attribute("perish_time"))) {
            m_hit = HitPerished;
        }
    }
}

