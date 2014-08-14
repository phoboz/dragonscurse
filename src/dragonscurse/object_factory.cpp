#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>
#include "world_db.h"
#include "player.h"
#include "coin.h"
#include "knight.h"
#include "dragon.h"
#include "climber.h"
#include "walker.h"
#include "crawler.h"
#include "erupter.h"
#include "guardian.h"
#include "shooter.h"
#include "diver.h"
#include "hovering.h"
#include "float.h"
#include "swimmer.h"
#include "dancer.h"
#include "falling.h"
#include "meka_dragon.h"
#include "key.h"
#include "arm.h"
#include "shield.h"
#include "armour.h"
#include "area.h"
#include "chest.h"
#include "curse.h"
#include "object_factory.h"

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
        if (strcmp(priv_object_type, "climber") == 0) {
            object = new Climber(name, media, x, y, dir);
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
        else if (strcmp(priv_object_type, "arm") == 0) {
            object = new Arm(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "shield") == 0) {
            object = new Shield(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "armour") == 0) {
            object = new Armour(name, media, x, y);
        }
    }
    else if (strcmp(type, "Walker") == 0) {
        object = new Walker(name, media, x, y, dir);
    }
    else if (strcmp(type, "Crawler") == 0) {
        object = new Crawler(name, media, x, y, dir);
    }
    else if (strcmp(type, "Erupter") == 0) {
        object = new Erupter(name, media, x, y, dir);
    }
    else if (strcmp(type, "Guardian") == 0) {
        object = new Guardian(name, media, x, y, dir);
    }
    else if (strcmp(type, "Shooter") == 0) {
        object = new Shooter(name, media, x, y, dir);
    }
    else if (strcmp(type, "Diver") == 0) {
        object = new Diver(name, media, x, y, dir);
    }
    else if (strcmp(type, "Hovering") == 0) {
        object = new Hovering(name, media, x, y, w, dir);
    }
    else if (strcmp(type, "Floater") == 0) {
        object = new Floater(name, media, x, y, dir);
    }
    else if (strcmp(type, "Swimmer") == 0) {
        object = new Swimmer(name, media, x, y, dir);
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
    else if (strcmp(type, "Chest") == 0) {
        object = new Chest(name, media, x, y);
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
    else if (dirname == std::string("up")) {
        object = create_object(name, media, type, x, y, w, h,
                               Object::Up, prop);
    }
    else if (dirname == std::string("down")) {
        object = create_object(name, media, type, x, y, w, h,
                               Object::Down, prop);
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

Object* ObjectFactory::create_object(ObjectInfo *info,
                                     MediaDB *media,
                                     int x, int y,
                                     int w, int h)
{
    Object *object = 0;

    switch(info->object_type) {
        case Object::TypeItem:
            object = ObjectFactory::create_object(info->data.item.name,
                                                  media, "Item");
            ((Item *) object)->set_world_key(info->key);
            break;

        case Object::TypeCurse:
            object = new Curse(info, media);
            break;

        default:
            break;
    }

    return object;
}

