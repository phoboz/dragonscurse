#ifndef _ObjectFactory_H
#define _ObjectFactory_H

#include "tinyxml.h"
#include "Tmx/TmxPropertySet.h"
#include "object.h"

struct ObjectInfo;

class ObjectFactory {
public:
    static Object* create_object(const char *name,
                                 MediaDB *media,
                                 const char *type,
                                 int x, int y,
                                 int w, int h,
                                 Object::Direction dir,
                                 const Tmx::PropertySet &prop);
    static Object* create_object(const char *name,
                                 MediaDB *media,
                                 const char *type,
                                 int x, int y,
                                 int w, int h,
                                 const Tmx::PropertySet &prop);
    static Object* create_object(const char *name,
                                 MediaDB *media,
                                 const char *type,
                                 int x = 0, int y = 0,
                                 int w = 0, int h = 0,
                                 Object::Direction dir = Object::Right);
    static Object* create_object(ObjectInfo *info,
                                 MediaDB *media,
                                 int x = 0, int y = 0,
                                 int w = 0, int h = 0);

private:
    static bool match_node_type(TiXmlElement *elmt);
    static bool search_nodes(TiXmlNode *node);
};

#endif

