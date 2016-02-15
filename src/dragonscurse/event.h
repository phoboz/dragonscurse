#ifndef _Event_H
#define _Event_H

#include "material.h"
#include "world_db.h"

class Event : public Material {
public:
    Event(int x, int y, EventInfo *info, MediaDB *media);
    ~Event();

    Object* get_event_object() const { return m_event_object; }

private:
    Object *m_event_object;
};

#endif

