#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>
#include "object_factory.h"
#include "player.h"
#include "knight.h"
#include "human.h"
#include "dragon.h"
#include "walker.h"
#include "guardian.h"
#include "lock_flyer.h"
#include "dancer.h"
#include "falling.h"
#include "meka_dragon.h"

Object* ObjectFactory::create_object(const char *name,
                                     const char *type,
                                     int x, int y,
                                     Object::Direction dir,
                                     const Tmx::PropertySet &prop)
{
    Object *object = 0;

    if (strcmp(type, "Player") == 0) {
        object = new Player(name, x, y, dir);
    }
    else if (strcmp(type, "Knight") == 0) {
        object = new Knight(name, x, y, dir);
    }
    else if (strcmp(type, "Human") == 0) {
        object = new Human(name, x, y, dir);
    }
    else if (strcmp(type, "Dragon") == 0) {
        object = new Dragon(name, x, y, dir);
    }
    else if (strcmp(type, "Walker") == 0) {
        object = new Walker(name, x, y, dir);
    }
    else if (strcmp(type, "Guardian") == 0) {
        object = new Guardian(name, x, y, dir);
    }
    else if (strcmp(type, "LockFlyer") == 0) {
        object = new LockFlyer(name, x, y, dir);
    }
    else if (strcmp(type, "Dancer") == 0) {
        object = new Dancer(name, x, y, dir);
    }
    else if (strcmp(type, "Falling") == 0) {
        object = new Falling(name, x, y, dir);
    }
    else if (strcmp(type, "MekaDragon") == 0) {
        object = new MekaDragon(name, x, y, dir);
    }

    if (object) {
        if (!object->get_loaded()) {
            delete object;
            object = 0;
        }
        std::map<std::string, std::string> pmap = prop.GetList();
        for (std::map<std::string, std::string>::const_iterator it = pmap.begin();
             it != pmap.end();
             ++it) {
            std::string name = it->first;
            if (name != std::string("direction")) {
                object->set_attribute(name.c_str(), atoi(it->second.c_str()));
            }
        }
    }

    return object;
}

Object* ObjectFactory::create_object(const char *name,
                                     const char *type,
                                     int x, int y,
                                     const Tmx::PropertySet &prop)
{
    Object *object;
    std::string dirname = prop.GetLiteralProperty(std::string("direction"));

    if (dirname == std::string("No such property!")) {
        object = create_object(name, type, x, y, Object::Right, prop);
    }
    else if (dirname == std::string("right")) {
        object = create_object(name, type, x, y, Object::Right, prop);
    }
    else if (dirname == std::string("left")) {
        object = create_object(name, type, x, y, Object::Left, prop);
    }

    return object;
}

Object* ObjectFactory::create_object(const char *name,
                                     const char *type,
                                     int x, int y,
                                     Object::Direction dir)
{
    Tmx::PropertySet prop;

    return create_object(name, type, x, y, dir, prop);
}

