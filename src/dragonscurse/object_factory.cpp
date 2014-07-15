#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>
#include "object_factory.h"
#include "player.h"
#include "coin.h"
#include "knight.h"
#include "human.h"
#include "dragon.h"
#include "walker.h"
#include "guardian.h"
#include "lock_flyer.h"
#include "dancer.h"
#include "falling.h"
#include "meka_dragon.h"
#include "key.h"
#include "shield.h"
#include "area.h"

static char priv_object_type[80];

bool ObjectFactory::match_node_type(TiXmlElement *elmt)
{
    bool result = false;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "type") == 0) {
            strcpy(priv_object_type, attr->Value());
            result = true;
        }

        attr = attr->Next();
    }

    return result;
}

bool ObjectFactory::search_nodes(TiXmlNode *node)
{
    int result = true;

    if (node->Type() == TiXmlNode::TINYXML_ELEMENT) {
        if (strcmp(node->Value(), "player") == 0) {
            result = match_node_type(node->ToElement());
        }
        else if (strcmp(node->Value(), "collectable") == 0) {
            result = match_node_type(node->ToElement());
        }
        else if (strcmp(node->Value(), "item") == 0) {
            result = match_node_type(node->ToElement());
        }
    }

    for (TiXmlNode *child = node->FirstChild();
             child != 0;
             child = child->NextSibling()) {
        if (!search_nodes(child)) {
            result = false;
        }
    }

    return result;
}

Object* ObjectFactory::create_object(const char *name,
                                     MediaDB *media,
                                     const char *type,
                                     int x, int y,
                                     int w, int h,
                                     Object::Direction dir,
                                     const Tmx::PropertySet &prop)
{
    Object *object = 0;

    if (strcmp(type, "Player") == 0) {
        TiXmlDocument doc(name);
        if (doc.LoadFile()) {
            search_nodes(&doc);
        }

        if (strcmp(priv_object_type, "knight") == 0) {
            object = new Knight(name, media, x, y, dir);
        }
        else if (strcmp(priv_object_type, "human") == 0) {
            object = new Human(name, media, x, y, dir);
        }
        else if (strcmp(priv_object_type, "dragon") == 0) {
            object = new Dragon(name, media, x, y, dir);
        }
        else {
            object = new Player(name, media, x, y, dir);
        }
    }
    else if (strcmp(type, "Collectable") == 0) {
        TiXmlDocument doc(name);
        if (doc.LoadFile()) {
            search_nodes(&doc);
        }

        if (strcmp(priv_object_type, "coin") == 0) {
            object = new Coin(name, media, x, y);
        }
    }
    else if (strcmp(type, "Item") == 0) {
        TiXmlDocument doc(name);
        if (doc.LoadFile()) {
            search_nodes(&doc);
        }

        if (strcmp(priv_object_type, "key") == 0) {
            object = new Key(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "shield") == 0) {
            object = new Shield(name, media, x, y);
        }
    }
    else if (strcmp(type, "Walker") == 0) {
        object = new Walker(name, media, x, y, dir);
    }
    else if (strcmp(type, "Guardian") == 0) {
        object = new Guardian(name, media, x, y, dir);
    }
    else if (strcmp(type, "LockFlyer") == 0) {
        object = new LockFlyer(name, media, x, y, dir);
    }
    else if (strcmp(type, "Dancer") == 0) {
        object = new Dancer(name, media, x, y, dir);
    }
    else if (strcmp(type, "Falling") == 0) {
        object = new Falling(name, media, x, y, dir);
    }
    else if (strcmp(type, "MekaDragon") == 0) {
        object = new MekaDragon(name, media, x, y, dir);
    }
    else if (strcmp(type, "Area") == 0) {
        std::string tn = prop.GetLiteralProperty(std::string("type"));
        object = new Area(name, media, tn.c_str(), x, y, w, h);
    }

    if (object) {
#ifdef TODO
        // Causes error now for areas
        if (!object->get_loaded()) {
            delete object;
            object = 0;
        }
#endif
        std::map<std::string, std::string> pmap = prop.GetList();
        for (std::map<std::string, std::string>::const_iterator it = pmap.begin();
             it != pmap.end();
             ++it) {
            std::string attr_name = it->first;
            if (attr_name != std::string("direction") &&
                attr_name != std::string("music")) {
                object->set_attribute(attr_name.c_str(),
                                      atoi(it->second.c_str()));
            }
        }
        object->initialize();
    }

    return object;
}

Object* ObjectFactory::create_object(const char *name,
                                     MediaDB *media,
                                     const char *type,
                                     int x, int y,
                                     int w, int h,
                                     const Tmx::PropertySet &prop)
{
    Object *object;
    std::string dirname = prop.GetLiteralProperty(std::string("direction"));

    if (dirname == std::string("No such property!")) {
        object = create_object(name, media, type, x, y, w, h,
                               Object::Right, prop);
    }
    else if (dirname == std::string("right")) {
        object = create_object(name, media, type, x, y, w, h,
                               Object::Right, prop);
    }
    else if (dirname == std::string("left")) {
        object = create_object(name, media, type, x, y, w, h,
                               Object::Left, prop);
    }

    std::string musicname = prop.GetLiteralProperty(std::string("music"));
    if (musicname != std::string("No such property!")) {
        object->set_string("music", musicname.c_str());
    }

    return object;
}

Object* ObjectFactory::create_object(const char *name,
                                     MediaDB *media,
                                     const char *type,
                                     int x, int y,
                                     int w, int h,
                                     Object::Direction dir)
{
    Tmx::PropertySet prop;

    return create_object(name, media, type, x, y, w, h, dir, prop);
}

