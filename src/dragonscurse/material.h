#ifndef _Material_H
#define _Material_H

#include "phoboz/timer.h"
#include "world.h"
#include "body.h"

class Material : public Body {
public:
    virtual void move(Map *map);

    void set_from_chest(bool value) { m_from_chest = value; }
    void set_world_key(int key) {
        m_world_key = key;
    }

    bool get_reachable() const { return m_reachable; }

    void aquire(WorldDB *db);
    void aquire(World *world);

protected:
    Material(Type type, const char *fn, MediaDB *media, int x, int y);

private:
    enum Action { Rise, Fall, Still };

    void animate_move();

    int m_world_key;
    bool m_from_chest;
    Timer m_rise_timer;
    Timer m_anim_timer;
    bool m_ref_done;
    bool m_reachable;
};

#endif

