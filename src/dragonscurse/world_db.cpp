#include "item.h"
#include "store_restore.h"
#include "world_db.h"

struct WorldNode {
    enum Type { TypeObject, TypeLock, TypeChest };

    WorldNode(Type type) : m_key(m_keygen++), m_type(type), m_user(0) { }

    static int m_keygen;

    int m_key;
    Type m_type;
    int m_user;
    std::string m_location;
    std::map<std::string, std::string> m_strings;
    std::map<std::string, int> m_integers;
};

struct WorldObject : public WorldNode {
    WorldObject() : WorldNode(TypeObject) { }
    Object::Type m_object_type;
};

struct WorldLock : public WorldNode {
    WorldLock() : WorldNode(TypeLock) { }
};

struct WorldChest : public WorldNode {
    WorldChest() : WorldNode(TypeChest) { }

    std::vector<WorldObject*> m_objects;
};

struct WorldLocation {
    std::list<WorldNode*> m_nodes;
};

int WorldNode::m_keygen;

bool WorldDB::load_world_attributes(TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "object_prefix") == 0) {
            m_object_prefix = std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "save_prefix") == 0) {
            m_save_prefix = std::string(attr->Value());
        }
        else {
            result = false;
            break;
        }

        attr = attr->Next();
    }

    return result;
}

bool WorldDB::load_object_attributes(WorldObject *object, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "id") == 0) {
            object->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "location_x") == 0) {
            object->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "location_y") == 0) {
            object->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "location") == 0) {
            object->m_location = std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "type") == 0) {
            if (strcmp(attr->Value(), "item") == 0) {
                object->m_object_type = Object::TypeItem;
            }
            else if (strcmp(attr->Value(), "collectable") == 0) {
                object->m_object_type = Object::TypeCollectable;
            }
            else if (strcmp(attr->Value(), "curse") == 0) {
                object->m_object_type = Object::TypeCurse;
            }
            else if (strcmp(attr->Value(), "event") == 0) {
                object->m_object_type = Object::TypeEvent;
            }
            else {
                result = false;
                break;
            }
        }
        else if (strcmp(attr->Name(), "name") == 0) {
            object->m_strings[std::string(attr->Name())] =
                std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "player") == 0) {
            object->m_strings[std::string(attr->Name())] =
                std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "destination") == 0) {
            object->m_strings[std::string(attr->Name())] =
                std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "start_x") == 0) {
            object->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "start_y") == 0) {
            object->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "event_type") == 0) {
            if (strcmp(attr->Value(), "area") == 0) {
                object->m_strings[std::string(attr->Name())] =
                    std::string(attr->Value());
            }
            else {
                result = false;
                break;
            }
        }
        else if (strcmp(attr->Name(), "event") == 0) {
            object->m_strings[std::string(attr->Name())] =
                std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "x") == 0) {
            object->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "y") == 0) {
            object->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "width") == 0) {
            object->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "height") == 0) {
            object->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "area_type") == 0) {
            object->m_strings[std::string(attr->Name())] =
                std::string(attr->Value());
        }
        else {
            result = false;
            break;
        }

        attr = attr->Next();
    }

    return result;
}

bool WorldDB::load_lock_attributes(WorldLock *lock, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "id") == 0) {
            lock->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "type") == 0) {
            lock->m_strings[std::string(attr->Name())] =
                std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "lock") == 0) {
            lock->m_strings[std::string(attr->Name())] =
                std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "once") == 0) {
            lock->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "location") == 0) {
            lock->m_location = std::string(attr->Value());
        }
        else {
            result = false;
            break;
        }

        attr = attr->Next();
    }

    return result;
}

bool WorldDB::load_chest_attributes(WorldChest *chest, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "id") == 0) {
            chest->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "once") == 0) {
            chest->m_integers[std::string(attr->Name())] = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "location") == 0) {
            chest->m_location = std::string(attr->Value());
        }
        else {
            result = false;
            break;
        }

        attr = attr->Next();
    }

    return result;
}

WorldLocation* WorldDB::find_location(const char *name) const
{
    WorldLocation *location;

    std::map<std::string, WorldLocation*>::const_iterator it =
        m_locations.find(name);
    if (it == m_locations.end()) {
        location = 0;
    }
    else {
        location = it->second;
    }

    return location;
}

WorldLocation* WorldDB::get_location(const char *name)
{
    // Check if location exists, otherwise allocate new and insert
    WorldLocation *location = find_location(name);
    if (!location) {
        location = new WorldLocation;
        m_locations[std::string(name)] = location;
    }

    return location;
}

bool WorldDB::load_nodes(TiXmlNode *node)
{
    int result = true;

    if (node->Type() == TiXmlNode::TINYXML_ELEMENT) {
        if (strcmp(node->Value(), "world") == 0) {
            result = load_world_attributes(node->ToElement());
        }
        else if (strcmp(node->Value(), "object") == 0) {
            WorldObject *object = new WorldObject;
            result = load_object_attributes(object, node->ToElement());
            if (result) {

                // Check if location exists, otherwise allocate new and insert
                WorldLocation *location =
                    get_location(object->m_location.c_str());
                if (location) {
                    location->m_nodes.push_back(object);
                }
            }
        }
        else if (strcmp(node->Value(), "lock") == 0) {
            WorldLock *lock = new WorldLock;
            result = load_lock_attributes(lock, node->ToElement());
            if (result) {

                // Check if location exists, otherwise allocate new and insert
                WorldLocation *location =
                    get_location(lock->m_location.c_str());
                if (location) {
                    location->m_nodes.push_back(lock);
                }
            }
        }
        else if (strcmp(node->Value(), "chest") == 0) {
            WorldChest *chest = new WorldChest;
            result = load_chest_attributes(chest, node->ToElement());
            if (result) {

                // Check if location exists, otherwise allocate new and insert
                WorldLocation *location =
                    get_location(chest->m_location.c_str());
                if (location) {
                    m_chest = chest;
                    location->m_nodes.push_back(chest);
                }
            }
        }
        else if (m_chest) {
            if (strcmp(node->Value(), "treasure") == 0) {
                WorldObject *object = new WorldObject;
                result = load_object_attributes(object, node->ToElement());
                if (result) {
                    m_chest->m_objects.push_back(object);
                }
                else {
                    goto error;
                }
            }
        }
    }

    for (TiXmlNode *child = node->FirstChild();
             child != 0;
             child = child->NextSibling()) {
        if (!load_nodes(child)) {
            result = false;
        }
    }

error:
    return result;
}

WorldDB::WorldDB(const char *name)
    : m_object_prefix(""),
      m_save_prefix(""),
      m_chest(0)
{
    WorldNode::m_keygen = 1;

    TiXmlDocument doc(name);
    if (doc.LoadFile()) {
        load_nodes(&doc);
        m_status = new Status;
    }
}

bool WorldDB::load_event_info(EventInfo *info, WorldObject *object) const
{
    bool result = false;

    info->location_x = object->m_integers["location_x"];
    info->location_y = object->m_integers["location_y"];
    info->event = object->m_strings[std::string("event")].c_str();
    if (object->m_strings[std::string("event_type")] == std::string("area")) {
        info->event_type = Object::TypeArea;
        result = true;
    }

    if (result) {
        switch (info->event_type) {
            case Object::TypeArea:
                info->data.area.x = object->m_integers["x"];
                info->data.area.y = object->m_integers["y"];
                info->data.area.width = object->m_integers["width"];
                info->data.area.height = object->m_integers["height"];
                info->data.area.name =
                    object->m_strings[std::string("name")].c_str();
                info->data.area.start_x = object->m_integers["start_x"];
                info->data.area.start_y = object->m_integers["start_y"];
                info->data.area.type =
                    object->m_strings[std::string("area_type")].c_str();
                break;

            default:
                result = false;
                break;
        }
    }

    return result;
}

bool WorldDB::load_object_info(ObjectInfo *info, WorldObject *object) const
{
    bool result = false;

    info->key = object->m_key;
    info->object_type = object->m_object_type;

    switch(object->m_object_type) {
        case Object::TypeItem:
            info->data.material.name =
                   object->m_strings[std::string("name")].c_str();
            result = true;
            break;

        case Object::TypeCollectable:
            info->data.material.name =
                   object->m_strings[std::string("name")].c_str();
            result = true;
            break;

        case Object::TypeCurse:
            info->data.curse.name =
                   object->m_strings[std::string("name")].c_str();
            info->data.curse.player =
                   object->m_strings[std::string("player")].c_str();
            info->data.curse.destination =
                   object->m_strings[std::string("destination")].c_str();
            info->data.curse.start_x =
                object->m_integers[std::string("start_x")];
            info->data.curse.start_y =
                object->m_integers[std::string("start_y")];
            result = true;
            break;

        case Object::TypeEvent:
            result = load_event_info(&info->data.event, object);
            break;

        default:
            break;
    }

    return result;
}

bool WorldDB::get_object_info(ObjectInfo *info,
                              int id, const char *location_name) const
{
    bool result = false;
    WorldLocation *location = find_location(location_name);

    if (location) {
        for (std::list<WorldNode*>::iterator it = location->m_nodes.begin();
             it != location->m_nodes.end();
             ++it) {
            if ((*it)->m_type == WorldNode::TypeObject) {
                WorldObject *object = (WorldObject *) *it;
                if (object->m_integers[std::string("id")] == id) {
                    result = load_object_info(info, object);
                }
            }
        }
    }

    return result;
}

bool WorldDB::get_object_info(ObjectInfo *info, int location_x, int location_y,
                              const char *location_name) const
{
    bool result = false;
    WorldLocation *location = find_location(location_name);

    if (location) {
        for (std::list<WorldNode*>::iterator it = location->m_nodes.begin();
             it != location->m_nodes.end();
             ++it) {
            if ((*it)->m_type == WorldNode::TypeObject) {
                WorldObject *object = (WorldObject *) *it;
                if (object->m_integers["location_x"] == location_x &&
                    object->m_integers["location_y"] == location_y) {
                    result = load_object_info(info, object);
                }
            }
        }
    }

    return result;
}

bool WorldDB::get_lock_info(LockInfo *info,
                            int id, const char *location_name) const
{
    bool result = false;
    WorldLocation *location = find_location(location_name);

    if (location) {
        for (std::list<WorldNode*>::iterator it = location->m_nodes.begin();
             it != location->m_nodes.end();
             ++it) {
            if ((*it)->m_type == WorldNode::TypeLock) {
                WorldLock *lock = (WorldLock *) *it;
                if (lock->m_integers[std::string("id")] == id) {
                    info->key = lock->m_key;
                    info->type_name =
                        lock->m_strings[std::string("type")].c_str();
                    info->lock_name =
                        lock->m_strings[std::string("lock")].c_str();
                    info->once = lock->m_integers["once"];
                    result = true;
                    break;
                }
            }
        }
    }

    return result;
}

bool WorldDB::get_chest_info(ChestInfo *info,
                             int id, const char *location_name) const
{
    bool result = false;
    WorldLocation *location = find_location(location_name);

    if (location) {
        for (std::list<WorldNode*>::iterator it = location->m_nodes.begin();
             it != location->m_nodes.end();
             ++it) {
            if ((*it)->m_type == WorldNode::TypeChest) {
                WorldChest *chest = (WorldChest *) *it;
                if (chest->m_integers[std::string("id")] == id) {
                    info->key = chest->m_key;
                    info->once = chest->m_integers["once"];
                    info->user = chest->m_user;
                    info->num_objects = chest->m_objects.size();
                    for (int i = 0; i < info->num_objects; i++) {
                        result = load_object_info(&info->objects[i],
                                                  chest->m_objects[i]);
                        if (!result) {
                            info->num_objects = i;
                            goto error;
                        }
                    }
                    break;
                }
            }
        }
    }

error:
    return result;
}

bool WorldDB::remove(int key)
{
    bool found = false;

    for (std::map<std::string, WorldLocation*>::iterator it =
             m_locations.begin();
         it!=m_locations.end();
         ++it) {
        WorldLocation *location = it->second;

        std::list<WorldNode*>::iterator jt = location->m_nodes.begin();
        for (;
             jt != location->m_nodes.end();
             ++jt) {
            if ((*jt)->m_key == key) {
                found = true;
                break;
            }
        }

        if (found) {
            m_removed_locations.push_back(key);
            location->m_nodes.erase(jt);
            goto end;
        }
    }

end:
    return found;
}

bool WorldDB::set_user(int key, int user)
{
    bool found = false;

    for (std::map<std::string, WorldLocation*>::iterator it =
             m_locations.begin();
         it!=m_locations.end();
         ++it) {
        WorldLocation *location = it->second;

        std::list<WorldNode*>::iterator jt = location->m_nodes.begin();
        for (;
             jt != location->m_nodes.end();
             ++jt) {
            if ((*jt)->m_key == key) {
                (*jt)->m_user = user;
                break;
            }
        }

        if (found) {
            location->m_nodes.erase(jt);
            goto end;
        }
    }

end:
    return found;
}

void WorldDB::clear_user()
{
    for (std::map<std::string, WorldLocation*>::iterator it =
             m_locations.begin();
         it!=m_locations.end();
         ++it) {
        WorldLocation *location = it->second;

        std::list<WorldNode*>::iterator jt = location->m_nodes.begin();
        for (;
             jt != location->m_nodes.end();
             ++jt) {
            (*jt)->m_user = 0;
        }
    }
}

bool WorldDB::store(const char *fn) const
{
    std::ofstream f;
    std::string pathname = m_save_prefix + fn;
    f.open(pathname.c_str(), std::ios::out | std::ios::binary);

    bool result = m_status->write(f);
    if (result) {
        int len = m_removed_locations.size();
        StoreRestore::write_integer(f, len);
        for (int i = 0; i < len; i++) {
           StoreRestore::write_integer(f, m_removed_locations[i]);
        }
    }

    f.close();

    return result;
}

bool WorldDB::restore(const char *fn, MediaDB *media)
{
    bool result = false;

    std::ifstream f;
    std::string pathname = m_save_prefix + fn;
    f.open(pathname.c_str(), std::ios::in | std::ios::binary);

    delete m_status;
    m_status = new Status;
    if (m_status && m_status->read(f, media)) {
        int num_removed_locations = StoreRestore::read_integer(f);
        for (int i = 0; i < num_removed_locations; i++) {
            remove(StoreRestore::read_integer(f));
        }
        result = true;
    }

    f.close();

    return result;
}

