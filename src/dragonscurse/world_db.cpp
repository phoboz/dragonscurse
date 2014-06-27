#include <list>
#include <string>
#include <map>
#include <string.h>
#include "world_db.h"

struct WorldNode {
    enum Type { TypeObject, TypeLock };

    WorldNode(Type type) : m_key(key_gen++), m_type(type) { }

    static int key_gen;

    int m_key;
    Type m_type;
    int m_id;
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

struct WorldLocation {
    std::list<WorldNode*> m_nodes;
};

int WorldNode::key_gen = 1;

bool WorldDB::load_object_attributes(WorldObject *object, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "id") == 0) {
            object->m_id = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "location") == 0) {
            object->m_location = std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "type") == 0) {
            if (strcmp(attr->Value(), "item") == 0) {
                object->m_object_type = Object::TypeItem;
            }
            else if (strcmp(attr->Value(), "curse") == 0) {
                object->m_object_type = Object::TypeCurse;
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
            lock->m_id = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "location") == 0) {
            lock->m_location = std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "type") == 0) {
            lock->m_strings[std::string(attr->Name())] =
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
        if (strcmp(node->Value(), "object") == 0) {
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
    }

    for (TiXmlNode *child = node->FirstChild();
             child != 0;
             child = child->NextSibling()) {
        if (!load_nodes(child)) {
            result = false;
        }
    }

    return result;
}

WorldDB::WorldDB(const char *name)
{
    TiXmlDocument doc(name);
    if (doc.LoadFile()) {
        load_nodes(&doc);
    }
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

                if (object->m_id == id) {
                    info->key = object->m_key;
                    info->object_type = object->m_object_type;

                    switch(object->m_object_type) {
                        case Object::TypeItem:
                            strcpy(info->data.item.name,
                                   object->m_strings[
                                       std::string("name")].c_str());
                            result = true;
                            break;

                        case Object::TypeCurse:
                            strcpy(info->data.curse.name,
                                   object->m_strings[
                                       std::string("name")].c_str());
                            strcpy(info->data.curse.player,
                                   object->m_strings[
                                       std::string("player")].c_str());
                            strcpy(info->data.curse.destination,
                                   object->m_strings[
                                       std::string("destination")].c_str());
                            info->data.curse.start_x =
                                object->m_integers[std::string("start_x")];
                            info->data.curse.start_y =
                                object->m_integers[std::string("start_y")];
                            result = true;
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }

    return result;
}

const char* WorldDB::get_lock_type(int *key,
                                   int id, const char *location_name) const
{
    WorldLocation *location = find_location(location_name);

    if (location) {
        for (std::list<WorldNode*>::iterator it = location->m_nodes.begin();
             it != location->m_nodes.end();
             ++it) {
            if ((*it)->m_type == WorldNode::TypeLock) {
                WorldLock *lock = (WorldLock *) *it;
                if (lock->m_id == id) {
                    *key = lock->m_key;
                    return lock->m_strings[std::string("type")].c_str();
                    break;
                }
            }
        }
    }

    return 0;
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
            location->m_nodes.erase(jt);
            goto end;
        }
    }

end:
    return found;
}

