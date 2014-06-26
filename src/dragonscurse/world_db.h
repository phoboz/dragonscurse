#ifndef _WorldDB_H
#define _WorldDB_H

#include <string>
#include <map>
#include "tinyxml.h"

struct WorldObject;
struct WorldLock;

struct WorldLocation;

class WorldDB {
public:
    WorldDB(const char *name);

    Object::Type get_object_type(int id, const char *location_name) const;
    const char* get_object_name(int *key,
                                int id, const char *location_name) const;
    const char* get_lock_type(int *key,
                              int id, const char *location_name) const;

    bool remove(int key);
private:
    bool load_object_attributes(WorldObject *object, TiXmlElement *elmt);
    bool load_lock_attributes(WorldLock *lock, TiXmlElement *elmt);

    WorldLocation* find_location(const char *name) const;
    WorldLocation* get_location(const char *name);
    bool load_nodes(TiXmlNode *node);

    std::map<std::string, WorldLocation*> m_locations;
};

#endif

