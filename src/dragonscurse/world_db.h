#ifndef _WorldDB_H
#define _WorldDB_H

#include <string>
#include <map>
#include "tinyxml.h"

struct WorldLock;
struct WorldItem;

struct WorldLocation;

class WorldDB {
public:
    enum LockType { LockTypeNone, LockTypeGreen, LockTypeRed };

    WorldDB(const char *name);

    const char* get_item_name(int id, const char *location_name) const;

    LockType get_lock_type(int id, const char *location_name) const;
    bool unlock(int id, const char *location_name) const;

private:
    bool load_item_attributes(WorldItem *item, TiXmlElement *elmt);
    bool load_lock_attributes(WorldLock *lock, TiXmlElement *elmt);

    WorldLocation* find_location(const char *name) const;
    WorldLocation* get_location(const char *name);
    bool load_nodes(TiXmlNode *node);

    std::map<std::string, WorldLocation*> m_locations;
};

#endif

