#include "area.h"
#include "event.h"

Event::Event(int x, int y, EventInfo *info, MediaDB *media)
    : Material(TypeEvent, info->event, media, x, y)
{
    switch(info->event_type) {
        case TypeArea:
            m_event_object = new Area(&info->data.area, media);
            break;

        default:
            m_event_object = 0;
            break;
    }
}

Event::~Event()
{
    if (m_event_object) {
        delete m_event_object;
    }
}

