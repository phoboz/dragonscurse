#ifndef _ObjectFactory_H
#define _ObjectFactory_H

#include "Tmx/TmxPropertySet.h"
#include "object.h"

class ObjectFactory {
public:
    static Object* create_object(const char *name,
                                 const char *type,
                                 int x, int y,
                                 Object::Direction dir,
                                 const Tmx::PropertySet &prop);
    static Object* create_object(const char *name,
                                 const char *type,
                                 int x, int y,
                                 const Tmx::PropertySet &prop);
    static Object* create_object(const char *name,
                                 const char *type,
                                 int x, int y,
                                 Object::Direction dir);
};

#endif

