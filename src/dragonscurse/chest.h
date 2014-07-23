#ifndef _Chest_H
#define _Chest_H

#include <list>
#include "phoboz/timer.h"
#include "object.h"

class WorldDB;
class Actor;

class Chest : public Object {
public:
    enum State { StateClosed, StateOpen };

    Chest(const char *fn, MediaDB *media, int x, int y);

    virtual void world_initialize(World *world);

    bool is_open(Actor *actor);
    Object* release_object();

    virtual void move(Map *map) { }

private:
    MediaDB *m_media;
    State m_state;
    WorldDB *m_db;
    int m_world_key;
    int m_once;
    std::list<Object*> m_objects;
    Timer m_object_timer;
};

#endif

