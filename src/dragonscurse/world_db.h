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
struct WorldEvent;
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
    ObjectInfo objects[16];
};

struct EventArea {
    int x;
    int y;
    int width;
    int height;
    const char *name;
    int start_x;
    int start_y;
    const char *area_type;
};

union EventData {
    EventArea area;
};

struct EventInfo {
    int key;
    enum Object::Type event_type;
    int location_x;
    int location_y;
    const char *event;
    EventData data;
};

class WorldDB {
public:
    WorldDB(const char *name);

    const char* get_object_prefix() const { return m_object_prefix.c_str(); }
    const char* get_save_prefix() const { return m_save_prefix.c_str(); }

    bool get_object_info(ObjectInfo *info,
                         int id, const char *location_name) const;

    bool get_lock_info(LockInfo *info,
                       int id, const char *location_name) const;

    bool get_chest_info(ChestInfo *info,
                        int id, const char *location_name) const;

    bool get_event_info(EventInfo *info,
                        int x, int y, const char *location_name) const;

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
    bool load_event_attributes(WorldEvent *chest, TiXmlElement *elmt);

    WorldLocation* find_location(const char *name) const;
    WorldLocation* get_location(const char *name);
    bool load_nodes(TiXmlNode *node);

    bool load_object_info(ObjectInfo *info, WorldObject *object) const;

    std::string m_object_prefix;
    std::string m_save_prefix;
    std::map<std::string, WorldLocation*> m_locations;
    WorldChest *m_chest;

    Status *m_status;
    std::vector<int> m_removed_locations;
};

#endif

