#include <map>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "world_db.h"
#include "player.h"
#include "coin.h"
#include "heart_container.h"
#include "heart_refill.h"
#include "potion.h"
#include "stone.h"
#include "break_rock.h"
#include "create_rock.h"
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
#include "floater.h"
#include "waver.h"
#include "swimmer.h"
#include "dancer.h"
#include "roller.h"
#include "falling.h"
#include "obstacle.h"
#include "meka_dragon.h"
#include "mummy_dragon.h"
#include "key.h"
#include "arm.h"
#include "shield.h"
#include "armour.h"
#include "area.h"
#include "chest.h"
#include "curse.h"
#include "event.h"
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

Object::Direction ObjectFactory::get_dir(const Tmx::Object *obj)
{
    Object::Direction dir = Object::Right;

    const Tmx::PropertySet prop = obj->GetProperties();
    std::string dirname = prop.GetLiteralProperty(std::string("direction"));

    if (dirname == std::string("right")) {
        dir = Object::Right;
    }
    else if (dirname == std::string("left")) {
        dir = Object::Left;
    }
    else if (dirname == std::string("up")) {
        dir = Object::Up;
    }
    else if (dirname == std::string("down")) {
        dir = Object::Down;
    }

    return dir;
}

Object* ObjectFactory::create_object(const char *name,
                                     MediaDB *media,
                                     const char *type,
                                     int x, int y,
                                     const Tmx::Object *obj)
{
    Object *object = 0;
    Object::Direction dir = Object::Right;

    if (!type && obj) {
        type = obj->GetType().c_str();
        if (!name) {
            name = obj->GetName().c_str();
        }
        x = obj->GetX();
        y = obj->GetY();
        dir = get_dir(obj);
    }

    if (strcmp(type, "Player") == 0) {
        std::string pathname = Object::get_prefix() + std::string(name);
        TiXmlDocument doc(pathname.c_str());
        if (doc.LoadFile()) {
            search_nodes(&doc);
        }

        if (strcmp(priv_object_type, "knight") == 0) {
            object = new Knight(name, media, x, y, dir);
        }
        else if (strcmp(priv_object_type, "climber") == 0) {
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
        std::string pathname = Object::get_prefix() + std::string(name);
        TiXmlDocument doc(pathname.c_str());
        if (doc.LoadFile()) {
            search_nodes(&doc);
        }

        if (strcmp(priv_object_type, "coin") == 0) {
            object = new Coin(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "heart_container") == 0) {
            object = new HeartContainer(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "heart_refill") == 0) {
            object = new HeartRefill(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "potion") == 0) {
            object = new Potion(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "stone") == 0) {
            object = new Stone(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "break_rock") == 0) {
            object = new BreakRock(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "create_rock") == 0) {
            object = new CreateRock(name, media, x, y);
        }
    }
    else if (strcmp(type, "Item") == 0) {
        std::string pathname = Object::get_prefix() + std::string(name);
        TiXmlDocument doc(pathname.c_str());
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
        if (obj) {
            object = new Hovering(name, media, x, y, obj->GetWidth(), dir);
        }
    }
    else if (strcmp(type, "Floater") == 0) {
        object = new Floater(name, media, x, y, dir);
    }
    else if (strcmp(type, "Waver") == 0) {
        object = new Waver(name, media, x, y, dir);
    }
    else if (strcmp(type, "Swimmer") == 0) {
        object = new Swimmer(name, media, x, y, dir);
    }
    else if (strcmp(type, "Dancer") == 0) {
        object = new Dancer(name, media, x, y, dir);
    }
    else if (strcmp(type, "Roller") == 0) {
        object = new Roller(name, media, x, y, obj->GetPolyline());
    }
    else if (strcmp(type, "Falling") == 0) {
        object = new Falling(name, media, x, y, dir);
    }
    else if (strcmp(type, "Obstacle") == 0) {
        object = new Obstacle(name, media, x, y, dir);
    }
    else if (strcmp(type, "MekaDragon") == 0) {
        object = new MekaDragon(name, media, x, y, dir);
    }
    else if (strcmp(type, "MummyDragon") == 0) {
        object = new MummyDragon(name, media, x, y, dir);
    }
    else if (strcmp(type, "Area") == 0) {
        if (obj) {
            const Tmx::PropertySet prop = obj->GetProperties();
            std::string tn = prop.GetLiteralProperty(std::string("type"));
            object = new Area(name, media, tn.c_str(),
                              x, y, obj->GetWidth(), obj->GetHeight());

            if (object) {
                std::string musicname =
                    prop.GetLiteralProperty(std::string("music"));
                if (musicname != std::string("No such property!")) {
                    object->set_string("music", musicname.c_str());
                }
            }
        }
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

        // Initialize all attributes in tmx mapfile
        if (obj) {
            const Tmx::PropertySet prop = obj->GetProperties();
            std::map<std::string, std::string> pmap = prop.GetList();
            for (std::map<std::string, std::string>::const_iterator it =
                     pmap.begin();
                 it != pmap.end();
                 ++it) {
                std::string attr_name = it->first;
                if (attr_name != std::string("direction") &&
                    attr_name != std::string("music")) {
                    object->set_attribute(attr_name.c_str(),
                                          atoi(it->second.c_str()));
                }
            }
        }

        object->initialize();
    }

    return object;
}

Object* ObjectFactory::create_object(ObjectInfo *info, MediaDB *media)
{
    Object *object = 0;

    switch(info->object_type) {
        case Object::TypeItem:
            object = ObjectFactory::create_object(info->data.material.name,
                                                  media, "Item", 0, 0, 0);
            ((Item *) object)->set_world_key(info->key);
            break;

        case Object::TypeCollectable:
            object = ObjectFactory::create_object(info->data.material.name,
                                                  media, "Collectable", 0, 0,
                                                  0);
            ((Collectable *) object)->set_world_key(info->key);
            break;

        case Object::TypeCurse:
            object = new Curse(info, media);
            break;

        case Object::TypeEvent:
            object = new Event(0, 0, &info->data.event, media);
            break;

        default:
            break;
    }

    return object;
}

