#include <iostream>
#include <string.h>
#include "object.h"

Object::~Object()
{
    if (m_loaded) {
        m_loaded = false;
        m_media->leave_sprite(m_spr);
    }
}

bool Object::load_object_attributes(TiXmlElement *elmt)
{
    std::string image;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "image") == 0) {
            image = std::string(attr->Value());
        }
        else {
            m_attributes[std::string(attr->Name())] = atoi(attr->Value());
        }

        attr = attr->Next();
    }

    m_spr = m_media->get_sprite(image.c_str());
    if (m_spr && m_spr->get_loaded()) {
        m_loaded = true;
    }

    return m_loaded;
}

void Object::load_strings(TiXmlElement *elmt)
{
    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        m_strings[std::string(attr->Name())] = std::string(attr->Value());
        attr = attr->Next();
    }
}

void Object::load_attributes(TiXmlElement *elmt)
{
    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        m_attributes[std::string(attr->Name())] = atoi(attr->Value());
        attr = attr->Next();
    }
}

bool Object::load_nodes(TiXmlNode *node)
{
    int result = true;

    if (node->Type() == TiXmlNode::TINYXML_ELEMENT) {
        if (strcmp(node->Value(), "object") == 0) {
            result = load_object_attributes(node->ToElement());
        }
        else if (strcmp(node->Value(), "string") == 0) {
            load_strings(node->ToElement());
        }
        else {
            load_attributes(node->ToElement());
        }
    }

    for (TiXmlNode *child = node->FirstChild();
             child != 0;
             child = child->NextSibling()) {
        if (!load_nodes(child)) {
            result = false;
        }
    }

    return result;
}

bool Object::load(const char *fn, MediaDB *media)
{
    m_media = media;

    TiXmlDocument doc(fn);
    if (doc.LoadFile()) {
        load_nodes(&doc);
        m_fn = std::string(fn);
    }

    return m_loaded;
}

bool Object::check_collision(int x, int y, Map *map, int id)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    int tile_id = map->get_tile_id(x, y, 0);
    if (!id) {
        if (tile_id >= prop.GetNumericProperty("solid_start") &&
            tile_id <= prop.GetNumericProperty("solid_end")) {
            result = true;
        }
    }
    else {
        if (tile_id == id) {
            result = true;
        }
    }

    return result;
}

bool Object::check_below(Map *map, int id)
{
    int bottom = get_attribute("bottom");
    int left = get_attribute("left");
    int right = get_attribute("right");
    int min_dy = m_dy;

    for (int i = left; i <= right; i++) {
        int dy;
        for (dy = m_dy; dy > 0; dy--) {
            if (!check_collision(m_x + i, m_y + bottom + dy, map, id)) {
                break;
            }
        }
        if (dy < min_dy) {
            min_dy = dy;
        }
    }

    bool result;
    if (min_dy != m_dy) {
        m_dy = min_dy;
        result = true;
    }
    else {
        result = false;
    }

    return result;
}

bool Object::check_ahead(Map *map, int id)
{
    int top = get_attribute("top");
    int bottom = get_attribute("bottom");
    int min_dx = m_dx;

    if (m_dir == Right) {
        int right = get_attribute("right");
        for (int i = top; i <= bottom; i++) {
            int dx;
            for (dx = m_dx; dx > 0; dx--) {
                if (!check_collision(m_x + right + dx, m_y + i, map, id)) {
                    break;
                }
            }
            if (dx < min_dx) {
                min_dx = dx;
            }
        }
    }
    else if (m_dir == Left) {
        int left = get_attribute("left");
        for (int i = top; i <= bottom; i++) {
            int dx;
            for (dx = m_dx; dx > 0; dx--) {
                if (!check_collision(m_x + left - dx, m_y + i, map, id)) {
                    break;
                }
            }
            if (dx < min_dx) {
                min_dx = dx;
            }
        }
    }

    bool result;
    if (min_dx != m_dx) {
        m_dx = min_dx;
        result = true;
    }
    else {
        result = false;
    }

    return result;
}

bool Object::check_behind(Map *map, int id)
{
    int top = get_attribute("top");
    int bottom = get_attribute("bottom");
    int min_dx = m_dx;

    if (m_dir == Right) {
        int left = get_attribute("left");
        for (int i = top; i <= bottom; i++) {
            int dx;
            for (dx = m_dx; dx > 0; dx--) {
                if (!check_collision(m_x + left - dx, m_y + i, map, id)) {
                    break;
                }
            }
            if (dx < min_dx) {
                min_dx = dx;
            }
        }
    }
    else if (m_dir == Left) {
        int right = get_attribute("right");
        for (int i = top; i <= bottom; i++) {
            int dx;
            for (dx = m_dx; dx > 0; dx--) {
                if (!check_collision(m_x + right + dx, m_y + i, map, id)) {
                    break;
                }
            }
            if (dx < min_dx) {
                min_dx = dx;
            }
        }
    }

    bool result;
    if (min_dx != m_dx) {
        m_dx = min_dx;
        result = true;
    }
    else {
        result = false;
    }

    return result;
}

bool Object::check_above(Map *map, int id)
{
    int top = get_attribute("top");
    int left = get_attribute("left");
    int right = get_attribute("right");
    int min_dy = m_dy;

    for (int i = left; i <= right; i++) {
        int dy;
        for (dy = m_dy; dy > 0; dy--) {
            if (!check_collision(m_x + i, m_y + top - dy, map, id)) {
                break;
            }
        }
        if (dy < min_dy) {
            min_dy = dy;
        }
    }

    bool result;
    if (min_dy != m_dy) {
        m_dy = min_dy;
        result = true;
    }
    else {
        result = false;
    }

    return result;
}

int Object::get_attribute(const char *name) const
{
    int value;

    std::map<std::string, int>::const_iterator it = m_attributes.find(name);
    if (it == m_attributes.end()) {
        value = 0;
    }
    else {
        value = it->second;
    }

    return value;
}

const char* Object::get_string(const char *name) const
{
    const char *str;

    std::map<std::string, std::string>::const_iterator it = m_strings.find(name);
    if (it == m_strings.end()) {
        str = 0;
    }
    else {
        str = it->second.c_str();
    }

    return str;
}

bool Object::get_visible(Map *map, int clip_x, int clip_y, int clip_w, int clip_h) const
{
    bool result;

    if (m_always_visible) {
        result = true;
    }
    else {
        int x = m_x - map->get_x();
        int y = m_y - map->get_y();

        if((x + m_spr->get_width() <= 0) || (x >= clip_w) ||
           (y + m_spr->get_height() <= 0) || (y >= clip_h)) {
            result = false;
        }
        else {
            result = true;
        }
    }

    return result;
}

