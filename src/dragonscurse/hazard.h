#ifndef _Hazard_H
#define _Hazard_H

#include <string>
#include "phoboz/map.h"
#include "object.h"

struct Hazard : public Object {
public:
    Hazard(const char *fn, MediaDB *media);

    bool get_hazard_range(int *start, int *end, Map *map);

    virtual void move(Map *map) { }

private:
    std::string m_start_name, m_end_name;
};

#endif

