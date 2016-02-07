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
                                 const Tmx::Object *obj);

    static Object* create_player(const char *name, MediaDB *media,
                                 int x = 0, int y = 0) {
        return create_object(name, media, "Player", x, y, 0);
    }

    static Object* create_item(const char *name, MediaDB *media) {
        return create_object(name, media, "Item", 0, 0, 0);
    }

    static Object* create_collectable(const char *name, MediaDB *media) {
        return create_object(name, media, "Collectable", 0, 0, 0);
    }

    static Object* create_object(ObjectInfo *info, MediaDB *media);

private:
    static bool match_node_type(TiXmlElement *elmt);
    static bool search_nodes(TiXmlNode *node);
    static Object::Direction get_dir(const Tmx::Object *obj);
};

#endif

