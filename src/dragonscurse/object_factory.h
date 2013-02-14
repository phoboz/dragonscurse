#ifndef _ObjectFactory_H
#define _ObjectFactory_H

#include "object.h"

class ObjectFactory {
public:
    static Object* create_object(const char *name,
                                 const char *type,
                                 int x, int y,
                                 Object::Direction dir);
    static Object* create_object(const char *name,
                                 const char *type,
                                 int x, int y,
                                 const char *dirname);
};

#endif
