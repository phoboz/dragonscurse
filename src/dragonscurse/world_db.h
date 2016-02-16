#ifndef _WorldDB_H
#define _WorldDB_H

#include <vector>
#include <string>
#include <map>
#include "phoboz/media_db.h"
#include "tinyxml.h"
#include "object.h"
#include "status.h"

struct WorldObject;
struct WorldLock;
struct WorldChest;
struct WorldLocation;

struct MaterialInfo {
    const char *name;
};

struct CurseInfo {
    const char *name;
    const char *player;
    const char *destination;
    int start_x;
    int start_y;
};

struct EventArea {
    int x;
    int y;
    int width;
    int height;
    const char *name;
    int start_x;
    int start_y;
    const char *type;
};

struct EventInfo {
    int key;
    enum Object::Type event_type;
    int location_x;
    int location_y;
    const char *event;
    union {
        EventArea area;
    } data;
};

struct ObjectInfo {
    int key;
    Object::Type object_type;
    union {
        MaterialInfo material;
        CurseInfo curse;
        EventInfo event;
    } data;
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
    ObjectInfo objects[16];
};

class WorldDB {
public:
    WorldDB(const char *name);

    const char* get_object_prefix() const { return m_object_prefix.c_str(); }
    const char* get_save_prefix() const { return m_save_prefix.c_str(); }

    bool get_object_info(ObjectInfo *info,
                         int id, const char *location_name) const;
    bool get_object_info(ObjectInfo *info, int location_x, int location_y,
                         const char *location_name) const;

    bool get_lock_info(LockInfo *info,
                       int id, const char *location_name) const;

    bool get_chest_info(ChestInfo *info,
                        int id, const char *location_name) const;

    bool remove(int key);
    bool set_user(int key, int user);
    void clear_user();

    Status* get_status() { return m_status; }
    bool store(const char *fn) const;
    bool restore(const char *fn, MediaDB *media);

private:
    bool load_world_attributes(TiXmlElement *elmt);
    bool load_object_attributes(WorldObject *object, TiXmlElement *elmt);
    bool load_lock_attributes(WorldLock *lock, TiXmlElement *elmt);
    bool load_chest_attributes(WorldChest *chest, TiXmlElement *elmt);

    WorldLocation* find_location(const char *name) const;
    WorldLocation* get_location(const char *name);
    bool load_nodes(TiXmlNode *node);

    bool load_event_info(EventInfo *info, WorldObject *object) const;
    bool load_object_info(ObjectInfo *info, WorldObject *object) const;

    std::string m_object_prefix;
    std::string m_save_prefix;
    std::map<std::string, WorldLocation*> m_locations;
    WorldChest *m_chest;

    Status *m_status;
    std::vector<int> m_removed_locations;
};

#endif

