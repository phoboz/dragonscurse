#include <iostream>
#include "object_factory.h"
#include "player.h"
#include "dragon.h"
#include "walker.h"

Object* ObjectFactory::create_object(const char *name,
                                     const char *type,
                                     int x, int y)
{
    Object *object = 0;

    if (strcmp(type, "Player") == 0) {
        object = new Player(name);
    }
    else if (strcmp(type, "Dragon") == 0) {
        object = new Dragon(name);
    }
    else if (strcmp(type, "Walker") == 0) {
        object = new Walker(name, x, y, Object::Left);
    }

    if (object) {
        if (!object->get_loaded()) {
            delete object;
            object = 0;
        }
    }

    return object;
}

