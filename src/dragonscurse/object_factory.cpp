#include <iostream>
#include <string.h>
#include "object_factory.h"
#include "player.h"
#include "dragon.h"
#include "walker.h"

Object* ObjectFactory::create_object(const char *name,
                                     const char *type,
                                     int x, int y,
                                     Object::Direction dir)
{
    Object *object = 0;

    if (strcmp(type, "Player") == 0) {
        object = new Player(name, x, y, dir);
    }
    else if (strcmp(type, "Dragon") == 0) {
        object = new Dragon(name, x, y, dir);
    }
    else if (strcmp(type, "Walker") == 0) {
        object = new Walker(name, x, y, dir);
    }

    if (object) {
        if (!object->get_loaded()) {
            delete object;
            object = 0;
        }
    }

    return object;
}

Object* ObjectFactory::create_object(const char *name,
                                     const char *type,
                                     int x, int y,
                                     const char *dirname)
{
    Object *object = 0;

    if (strcmp(dirname, "right") == 0) {
        object = create_object(name, type, x, y, Object::Right);
    }
    else if (strcmp(dirname, "left") == 0) {
        object = create_object(name, type, x, y, Object::Left);
    }

    return object;
}

