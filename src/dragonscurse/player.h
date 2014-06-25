#ifndef _Player_H
#define _Player_H

#include <list>
#include "phoboz/timer.h"
#include "actor.h"

class Item;

class Player : public Actor {
public:
    Player(const char *fn, int x, int y, Direction dir)
        : Actor(Object::TypePlayer, x, y, dir),
          m_jump_ready(true) { load(fn); }

    virtual bool set_hit(Object *object);
    virtual bool check_collision(Object *object);
    virtual bool attack_actor(Actor *actor) { return false; }
    virtual void move(Map *map);

    void aquire_item(Item *item) { m_items.push_back(item); }
    Item* check_item(const char *name);
    void remove_item(Item *item) { m_items.remove(item); }

private:
    bool m_jump_ready;
    Timer m_jump_timer;
    Timer m_hit_timer;
    std::list<Item*> m_items;
};

#endif

