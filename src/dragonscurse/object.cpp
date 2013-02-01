#include <stdio.h>
#include <string.h>
#include "object.h"

Object::~Object()
{
    if (m_loaded) {
        m_loaded = false;
        delete m_spr;
    }
}

bool Object::load_object_attributes(TiXmlElement *elmt)
{
    std::string image;
    int w, h, margin, spacing;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "image") == 0) {
            image = std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "width") == 0) {
            w = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "height") == 0) {
            h = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "margin") == 0) {
            margin = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "spacing") == 0) {
            spacing = atoi(attr->Value());
        }
        else {
            m_attributes[std::string(attr->Name())] = atoi(attr->Value());
        }

        attr = attr->Next();
    }

    m_spr = new Sprite(image.c_str(), w, h, margin, spacing);
    if (m_spr->get_loaded()) {
        m_loaded = true;
    }

    return m_loaded;
}

void Object::load_extra_attributes(TiXmlElement *elmt)
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
        else {
            load_extra_attributes(node->ToElement());
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

bool Object::load(const char *fn)
{
    TiXmlDocument doc(fn);
    if (doc.LoadFile()) {
        load_nodes(&doc);
    }

    return m_loaded;
}

bool Object::check_collision(int x, int y, Map *map)
{
    bool result = false;

    int tile_id = map->get_tile_id(x, y, 0);
    if (tile_id <= 14) {
#if 0
        const Sprite *tiles = map->get_tileset(0);
        int tw = tiles->get_width();
        int th = tiles->get_height();
        int mx = map->get_x();
        int my = map->get_y();
        int tx = (x / tw) * tw - mx;
        int ty = (y / th) * th - my;

        if (m_spr->check_collision(m_frame, x - mx, y - my,
                                   tiles, tile_id, tx, ty)) {
            result = true;
        }
#else
        result = true;
#endif
    }

    return result;
}

bool Object::check_below(Map *map)
{
    int bottom = get_attribute("bottom");
    int min_dy = m_dy;

    if (m_dir == Right) {
        int right = get_attribute("right");
        for (int i = 0; i < right; i++) {
            int dy;
            for (dy = m_dy; dy > 0; dy--) {
                if (!check_collision(m_x + i, m_y + bottom + dy, map)) {
                    break;
                }
            }
            if (dy < min_dy) {
                min_dy = dy;
            }
        }
    }
    else if (m_dir == Left) {
        int left = get_attribute("left");
        int w = m_spr->get_width();
        for (int i = left; i < w; i++) {
            int dy;
            for (dy = m_dy; dy > 0; dy--) {
                if (!check_collision(m_x + i, m_y + bottom + dy, map)) {
                    break;
                }
            }
            if (dy < min_dy) {
                min_dy = dy;
            }
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

bool Object::check_ahead(Map *map)
{
    int top = get_attribute("top");
    int bottom = get_attribute("bottom");
    int min_dx = m_dx;

    if (m_dir == Right) {
        int right = get_attribute("right");
        for (int i = top; i < bottom; i++) {
            int dx;
            for (dx = m_dx; dx > 0; dx--) {
                if (!check_collision(m_x + right + dx, m_y + i, map)) {
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
        for (int i = top; i < bottom; i++) {
            int dx;
            for (dx = m_dx; dx > 0; dx--) {
                // TODO: For some reason a 2 has to be substracted
                if (!check_collision(m_x + left - dx, m_y + i, map)) {
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

bool Object::check_above(Map *map)
{
    int top = get_attribute("top");
    int min_dy = m_dy;

    if (m_dir == Right) {
        int right = get_attribute("right");
        for (int i = 0; i < right; i++) {
            int dy;
            for (dy = m_dy; dy > 0; dy--) {
                if (!check_collision(m_x + i, m_y + top - dy, map)) {
                    break;
                }
            }
            if (dy < min_dy) {
                min_dy = dy;
            }
        }
    }
    else if (m_dir == Left) {
        int left = get_attribute("left");
        int w = m_spr->get_width();
        for (int i = left; i < w; i++) {
            int dy;
            for (dy = m_dy; dy > 0; dy--) {
                if (!check_collision(m_x + i, m_y + top - dy, map)) {
                    break;
                }
            }
            if (dy < min_dy) {
                min_dy = dy;
            }
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

bool Object::set_dir(Direction dir)
{
    if (dir == Keep || dir == m_dir) {
        return false;
    }

    m_anim_dir = AnimUp;
    switch(dir) {
        case Right:
            m_frame = get_attribute("right_walk_start");
            m_dir = dir;
            break;

        case Left:
            m_frame = get_attribute("left_walk_start");
            m_dir = dir;
            break;

        default:
            return false;
    }

    return true;
}

bool Object::set_stand(void)
{
    bool done = false;

    if (++m_counter == get_attribute("treshold")) {
        m_counter = 0;
        m_anim_dir = AnimUp;
        m_action = Stand;
        done = true;
        switch(m_dir) {
            case Right:
                m_frame = get_attribute("right_stand");
                break;

            case Left:
                m_frame = get_attribute("left_stand");
                break;

            default:
                break;
        }
    }

    return done;
}

void Object::set_jump()
{
    m_action = Jump;
    switch(m_dir) {
        case Right:
            m_frame = get_attribute("right_jump");
            break;

        case Left:
            m_frame = get_attribute("left_jump");
            break;

        default:
            break;
    }
}

void Object::set_crouch(void)
{
    m_action = Crouch;
    switch(m_dir) {
        case Right:
            m_frame = get_attribute("right_crouch");
            break;

        case Left:
            m_frame = get_attribute("left_crouch");
            break;

        default:
            break;
    }
}

void Object::animate_walk()
{
    if (++m_counter == get_attribute("treshold")) {
        m_counter = 0;
        switch(m_dir) {
            case Right:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame == get_attribute("right_walk_end")) {
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame == get_attribute("right_walk_start")) {
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            case Left:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame == get_attribute("left_walk_end")) {
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame == get_attribute("left_walk_start")) {
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            default:
                break;
        }
    }
}

