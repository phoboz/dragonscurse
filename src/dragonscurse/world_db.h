#ifndef _WorldDB_H
#define _WorldDB_H

#include <list>
#include <string>
#include "tinyxml.h"

struct Lock;

class WorldDB {
public:
    enum KeyType { KeyTypeGreen, KeyTypeRed };

    WorldDB(const char *name);

private:
    bool load_attributes(Lock *lock, TiXmlElement *elmt);
    bool load_nodes(TiXmlNode *node);

    std::list<Lock*> m_locks;
};

#endif

