#ifndef _WorldDB_H
#define _WorldDB_H

#include <string>
#include <map>
#include "tinyxml.h"
#include "object.h"
#include "status.h"

struct WorldObject;
struct WorldLock;
struct WorldChest;
struct WorldLocation;

struct MaterialData {
    char name[80];
};

struct CurseData {
    char name[80];
    char player[80];
    char destination[80];
    int start_x;
    int start_y;
};

union ObjectData {
    MaterialData material;
    CurseData curse;
};

struct ObjectInfo {
    int key;
    Object::Type object_type;
    ObjectData data;
};

struct LockInfo {
    int key;
    const char *type_name;
    const char *lock_name;
    int once;
};

struct ChestInfo {
    int key;
    int once;
    int user;
    int num_objects;
    ObjectInfo objects[10];
};

class WorldDB {
public:
    WorldDB(const char *name);

    bool get_object_info(ObjectInfo *info,
                         int id, const char *location_name) const;

    bool get_lock_info(LockInfo *info,
                       int id, const char *location_name) const;

    bool get_chest_info(ChestInfo *info,
                        int id, const char *location_name) const;

    bool remove(int key);
    bool set_user(int key, int user);
    void clear_user();

    Status* get_status() { return &m_status; }

private:
    bool load_object_attributes(WorldObject *object, TiXmlElement *elmt);
    bool load_lock_attributes(WorldLock *lock, TiXmlElement *elmt);
    bool load_chest_attributes(WorldChest *chest, TiXmlElement *elmt);

    WorldLocation* find_location(const char *name) const;
    WorldLocation* get_location(const char *name);
    bool load_nodes(TiXmlNode *node);

    bool load_object_info(ObjectInfo *info, WorldObject *object) const;

    std::map<std::string, WorldLocation*> m_locations;
    WorldChest *m_chest;

    Status m_status;
};

#endif

