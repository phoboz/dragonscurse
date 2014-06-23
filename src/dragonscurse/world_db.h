#ifndef _WorldDB_H
#define _WorldDB_H

#include <string>
#include <map>
#include "tinyxml.h"

struct Lock;
struct WorldLocation;

class WorldDB {
public:
    enum LockType { LockTypeNone, LockTypeGreen, LockTypeRed };

    WorldDB(const char *name);

    LockType get_lock_type(int id, const char *location_name) const;
    bool unlock(int id, const char *location_name) const;

private:
    bool load_attributes(Lock *lock, TiXmlElement *elmt);
    WorldLocation* find_location(const char *name) const;
    bool load_nodes(TiXmlNode *node);

    std::map<std::string, WorldLocation*> m_locations;
};

#endif

