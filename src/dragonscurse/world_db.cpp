#include <list>
#include <string>
#include <string.h>
#include "world_db.h"

struct Lock {
    int m_id;
    WorldDB::LockType m_type;
    std::string m_location;
};

struct WorldLocation {
    std::list<Lock*> m_locks;
};

bool WorldDB::load_attributes(Lock *lock, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "id") == 0) {
            lock->m_id = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "type") == 0) {
            if (strcmp(attr->Value(), "green") == 0) {
                lock->m_type = LockTypeGreen;
            }
            else if (strcmp(attr->Value(), "red") == 0) {
                lock->m_type = LockTypeRed;
            }
            else {
                result = false;
                break;
            }
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

bool WorldDB::load_nodes(TiXmlNode *node)
{
    int result = true;

    if (node->Type() == TiXmlNode::TINYXML_ELEMENT) {
        if (strcmp(node->Value(), "lock") == 0) {
            Lock *lock = new Lock;
            result = load_attributes(lock, node->ToElement());
            if (result) {

                // Check if location exists, otherwise allocate new and insert
                WorldLocation *location =
                    find_location(lock->m_location.c_str());
                if (!location) {
                    location = new WorldLocation;
                    m_locations[lock->m_location] = location;
                }

                // Add lock to location
                location->m_locks.push_back(lock);
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

WorldDB::LockType WorldDB::get_lock_type(int id, const char *location_name) const
{
    LockType result = LockTypeNone;
    WorldLocation *location = find_location(location_name);

    if (location) {
        for (std::list<Lock*>::iterator it = location->m_locks.begin();
             it != location->m_locks.end();
             ++it) {
            Lock *lock = *it;
            if (lock->m_id == id) {
                result = lock->m_type;
                break;
            }
        }
    }

    return result;
}

bool WorldDB::unlock(int id, const char *location_name) const
{
    bool result = false;
    WorldLocation *location = find_location(location_name);

    if (location) {
        std::list<Lock*>::iterator it = location->m_locks.begin();
        for (;
             it != location->m_locks.end();
             ++it) {
            Lock *lock = *it;
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

