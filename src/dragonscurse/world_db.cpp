#include <list>
#include <string>
#include <string.h>
#include "world_db.h"

struct WorldItem {
    int m_id;
    std::string m_name;
    std::string m_location;
};

struct WorldLock {
    int m_id;
    std::string m_type;
    std::string m_location;
};

struct WorldLocation {
    std::list<WorldItem*> m_items;
    std::list<WorldLock*> m_locks;
};

bool WorldDB::load_item_attributes(WorldItem *item, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "id") == 0) {
            item->m_id = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "name") == 0) {
            item->m_name = std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "location") == 0) {
            item->m_location = std::string(attr->Value());
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
        else if (strcmp(attr->Name(), "type") == 0) {
            lock->m_type = std::string(attr->Value());
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
        if (strcmp(node->Value(), "item") == 0) {
            WorldItem *item = new WorldItem;
            result = load_item_attributes(item, node->ToElement());
            if (result) {

                // Check if location exists, otherwise allocate new and insert
                WorldLocation *location =
                    get_location(item->m_location.c_str());
                if (location) {
                    location->m_items.push_back(item);
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
                    location->m_locks.push_back(lock);
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

const char* WorldDB::get_item_name(int id, const char *location_name) const
{
    WorldLocation *location = find_location(location_name);

    if (location) {
        for (std::list<WorldItem*>::iterator it = location->m_items.begin();
             it != location->m_items.end();
             ++it) {
            WorldItem *item = *it;
            if (item->m_id == id) {
                return item->m_name.c_str();
                break;
            }
        }
    }

    return 0;
}

bool WorldDB::take_item(int id, const char *location_name)
{
    bool result = false;
    WorldLocation *location = find_location(location_name);

    if (location) {
        std::list<WorldItem*>::iterator it = location->m_items.begin();
        for (;
             it != location->m_items.end();
             ++it) {
            WorldItem *item = *it;
            if (item->m_id == id) {
                result = true;
                break;
            }
        }

        if (result) {
            location->m_items.erase(it);
        }
    }

    return result;
}

const char* WorldDB::get_lock_type(int id, const char *location_name) const
{
    WorldLocation *location = find_location(location_name);

    if (location) {
        for (std::list<WorldLock*>::iterator it = location->m_locks.begin();
             it != location->m_locks.end();
             ++it) {
            WorldLock *lock = *it;
            if (lock->m_id == id) {
                return lock->m_type.c_str();
                break;
            }
        }
    }

    return 0;
}

bool WorldDB::unlock(int id, const char *location_name)
{
    bool result = false;
    WorldLocation *location = find_location(location_name);

    if (location) {
        std::list<WorldLock*>::iterator it = location->m_locks.begin();
        for (;
             it != location->m_locks.end();
             ++it) {
            WorldLock *lock = *it;
            if (lock->m_id == id) {
                result = true;
                break;
            }
        }

        if (result) {
            location->m_locks.erase(it);
        }
    }

    return result;
}

