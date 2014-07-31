#include <string.h>
#include "object.h"

struct CollisionPart {
    int x1, y1;
    int x2, y2;
};

struct CollisionParts {
    int m_frame;
    std::vector<CollisionPart*> m_parts;

    CollisionParts(TiXmlElement *elmt) {
        TiXmlAttribute *attr = elmt->FirstAttribute();
        while (attr) {
            if (strcmp(attr->Name(), "frame") == 0) {
                m_frame = atoi(attr->Value());
            }
            attr = attr->Next();
        }
    }

    void add_parts(TiXmlElement *elmt) {
        CollisionPart *part = new CollisionPart;
        TiXmlAttribute *attr = elmt->FirstAttribute();
        while (attr) {
            if (strcmp(attr->Name(), "x1") == 0) {
                part->x1 = atoi(attr->Value());
            }
            else if (strcmp(attr->Name(), "y1") == 0) {
                part->y1 = atoi(attr->Value());
            }
            else if (strcmp(attr->Name(), "x2") == 0) {
                part->x2 = atoi(attr->Value());
            }
            else if (strcmp(attr->Name(), "y2") == 0) {
                part->y2 = atoi(attr->Value());
            }
            attr = attr->Next();
        }
        m_parts.push_back(part);
    }
};

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
        else if (strcmp(node->Value(), "weak_parts") == 0) {
            m_weak_parts.push_back(new CollisionParts(node->ToElement()));
        }
        else if (strcmp(node->Value(), "weak_part") == 0) {
            if (m_weak_parts.size()) {
                CollisionParts *parts = m_weak_parts.back();
                parts->add_parts(node->ToElement());
             }
        }
        else if (strcmp(node->Value(), "shielded_parts") == 0) {
            m_shielded_parts.push_back(new CollisionParts(node->ToElement()));
        }
        else if (strcmp(node->Value(), "shielded_part") == 0) {
            if (m_shielded_parts.size()) {
                CollisionParts *parts = m_shielded_parts.back();
                parts->add_parts(node->ToElement());
             }
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
        int lastindex = m_fn.find_last_of(".");
        m_name = m_fn.substr(0, lastindex);

    }

    return m_loaded;
}

Object::Direction Object::get_reference() const
{
    Direction dir;

    // Right of reference
    if (m_x < m_xref) {
        dir = Right;
    }
    else {
        dir = Left;
    }

    return dir;
}

int Object::get_front() const
{
    int result;

    switch(m_dir) {
        case Right:
            result = m_x + get_attribute("right");
            break;

        case Left:
            result = m_x + get_attribute("left");
            break;

        default:
            result = 0;
            break;
    }

    return result;
}

int Object::get_bottom() const
{
    return m_y + get_attribute("bottom");
}

bool Object::check_collision(int x, int y, Map *map, int start, int end)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    int tile_id = map->get_tile_id(x, y, 0);
    if (!start) {
        if (tile_id >= prop.GetNumericProperty("solid_start") &&
            tile_id <= prop.GetNumericProperty("solid_end")) {
            result = true;
        }
    }
    else {
        if (!end) {
            end = start;
        }
        if (tile_id >= start && tile_id <= end) {
            result = true;
        }
    }

    return result;
}

bool Object::check_center(Map *map, int start, int end)
{
    int x = m_x + get_attribute("right") - get_attribute("left");
    int y = m_y + get_attribute("bottom") - get_attribute("top");

    return check_collision(x, y, map, start, end);
}

bool Object::check_below(Map *map, int start, int end)
{
    bool result = false;
    int min_dy = check_below(map, m_dy, start, end);

    if (min_dy != m_dy) {
        m_dy = min_dy;
        result = true;
    }

    return result;
}

int Object::check_below(Map *map, int len, int start, int end)
{
    int result = len;
    int bottom = get_attribute("bottom");
    int left = get_attribute("left");
    int right = get_attribute("right");

    for (int i = left; i <= right; i++) {
        int dy;
        for (dy = len; dy > 0; dy--) {
            if (!check_collision(m_x + i, m_y + bottom + dy,
                                 map, start, end)) {
                break;
            }
        }
        if (dy < result) {
            result = dy;
        }
    }

    return result;
}

bool Object::check_ahead(Map *map, int start, int end)
{
    bool result = false;
    int min_dx = check_ahead(map, m_dx, start, end);

    if (min_dx != m_dx) {
        m_dx = min_dx;
        result = true;
    }

    return result;
}

int Object::check_ahead(Map *map, int len, int start, int end)
{
    int result = len;
    int top = get_attribute("top");
    int bottom = get_attribute("bottom");

    if (m_dir == Right) {
        int right = get_attribute("right");
        for (int i = top; i <= bottom; i++) {
            int dx;
            for (dx = len; dx > 0; dx--) {
                if (!check_collision(m_x + right + dx, m_y + i,
                                     map, start, end)) {
                    break;
                }
            }
            if (dx < result) {
                result = dx;
            }
        }
    }
    else if (m_dir == Left) {
        int left = get_attribute("left");
        for (int i = top; i <= bottom; i++) {
            int dx;
            for (dx = len; dx > 0; dx--) {
                if (!check_collision(m_x + left - dx, m_y + i,
                                     map, start, end)) {
                    break;
                }
            }
            if (dx < result) {
                result = dx;
            }
        }
    }

    return result;
}

bool Object::check_behind(Map *map, int start, int end)
{
    int top = get_attribute("top");
    int bottom = get_attribute("bottom");
    int min_dx = m_dx;

    if (m_dir == Right) {
        int left = get_attribute("left");
        for (int i = top; i <= bottom; i++) {
            int dx;
            for (dx = m_dx; dx > 0; dx--) {
                if (!check_collision(m_x + left - dx, m_y + i,
                                     map, start, end)) {
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
                if (!check_collision(m_x + right + dx, m_y + i,
                                     map, start, end)) {
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

bool Object::check_above(Map *map, int start, int end)
{
    bool result = false;
    int min_dy = check_above(map, m_dy, start, end);

    if (min_dy != m_dy) {
        m_dy = min_dy;
        result = true;
    }

    return result;
}

int Object::check_above(Map *map, int len, int start, int end)
{
    int result = len;
    int top = get_attribute("top");
    int left = get_attribute("left");
    int right = get_attribute("right");

    for (int i = left; i <= right; i++) {
        int dy;
        for (dy = len; dy > 0; dy--) {
            if (!check_collision(m_x + i, m_y + top - dy,
                                 map, start, end)) {
                break;
            }
        }
        if (dy < result) {
            result = dy;
        }
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

CollisionParts* Object::find_collision_parts(std::vector<CollisionParts*> v) const
{
    CollisionParts *parts = 0;

    for (int i = 0; i < v.size(); i++) {
        if (v[i]->m_frame == m_frame) {
            parts = v[i];
            break;
        }
        else if (v[i]->m_frame == -1) {
            parts = v[i];
        }
    }

    return parts;
}

bool Object::check_weak_collision(Object *object) const
{
    bool result = false;
    CollisionParts *parts = find_collision_parts(m_weak_parts);

    if (parts) {
        const Sprite *spr = object->get_sprite();
        for (int i = 0; i < parts->m_parts.size(); i++) {
            CollisionPart *part = parts->m_parts[i];
            result = spr->check_collision(object->get_frame(),
                                          object->get_x(),
                                          object->get_y(),
                                          get_sprite(), m_frame,
                                          m_x, m_y,
                                          part->x1,
                                          part->y1,
                                          part->x2,
                                          part->y2);
            if (result) {
                break;
            }
        }
    }

    return result;
}

bool Object::check_weak_collision(Object *object,
                                  int start_x1, int start_y1,
                                  int end_x1, int end_y1) const
{
    bool result = false;
    CollisionParts *parts = find_collision_parts(m_weak_parts);

    if (parts) {
        const Sprite *spr = object->get_sprite();
        for (int i = 0; i < parts->m_parts.size(); i++) {
            CollisionPart *part = parts->m_parts[i];
            result = spr->check_collision(object->get_frame(),
                                          object->get_x(),
                                          object->get_y(),
                                          start_x1, start_y1,
                                          end_x1, end_y1,
                                          get_sprite(), m_frame,
                                          m_x, m_y,
                                          part->x1,
                                          part->y1,
                                          part->x2,
                                          part->y2);
            if (result) {
                break;
            }
        }
    }

    return result;
}

bool Object::check_shielded_collision(Object *object) const
{
    bool result = false;
    CollisionParts *parts = find_collision_parts(m_shielded_parts);

    if (parts) {
        const Sprite *spr = object->get_sprite();
        for (int i = 0; i < parts->m_parts.size(); i++) {
            CollisionPart *part = parts->m_parts[i];
            result = spr->check_collision(object->get_frame(),
                                          object->get_x(),
                                          object->get_y(),
                                          get_sprite(), m_frame,
                                          m_x, m_y,
                                          part->x1,
                                          part->y1,
                                          part->x2,
                                          part->y2);
            if (result) {
                break;
            }
        }
    }

    return result;
}

