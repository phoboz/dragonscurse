#ifndef _LockDB_H
#define _LockDB_H

#include <list>
#include <string>
#include "tinyxml.h"

struct Lock;

class LockDB {
public:
    LockDB(const char *name);

private:
    bool load_attributes(Lock *lock, TiXmlElement *elmt);
    bool load_nodes(TiXmlNode *node);

    std::list<Lock*> m_locks;
};

#endif

