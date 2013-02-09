#ifndef _Object_H
#define _Object_H

#include <string>
#include <map>
#include "tinyxml.h"
#include "phoboz/sprite.h"
#include "phoboz/map.h"

class Object {
public:
    enum Type { TypePlayer, TypeEnemy, TypeBullet };
    enum Direction { Keep, Right, Left };

    Object(Type type)
        : m_x(0), m_y(0), m_dx(0), m_dy(0), m_frame(0),
          m_dir(Right), m_loaded(false), m_type(type) { }
    Object(Type type, int x, int y, Direction dir)
        : m_x(x), m_y(y), m_dx(0), m_dy(0), m_frame(0),
          m_dir(dir), m_loaded(false), m_type(type) { }
    ~Object();
    bool load(const char *fn);
    bool get_loaded() const { return m_loaded; }
    int get_x() const { return m_x; }
    int get_y() const { return m_y; }
    int get_image_width() const { return m_spr->get_image_width(); }
    int get_image_height() const { return m_spr->get_image_height(); }
    void set_x(int value) { m_x = value; }
    void set_y(int value) { m_y = value; }
    virtual void move(Map *map) = 0;
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h) const {
        m_spr->draw(dest, m_x - map->get_x(), m_y - map->get_y(), m_frame,
                    clip_x, clip_y, clip_w, clip_h);
    }

protected:
    int  get_attribute(const char *name) {
        return m_attributes[std::string(name)];
    }
    const char* get_string(const char *name) {
        return m_strings[std::string(name)].c_str();
    }

    bool check_collision(int x, int y, Map *map);
    bool check_below(Map *map);
    bool check_ahead(Map *map);
    bool check_above(Map *map);

    std::map<std::string, int> m_attributes;
    std::map<std::string, std::string> m_strings;

    int m_x, m_y;
    int m_dx, m_dy;
    int m_frame;
    Direction m_dir;
    Sprite *m_spr;

private:
    bool load_object_attributes(TiXmlElement *elmt);
    void load_strings(TiXmlElement *elmt);
    void load_attributes(TiXmlElement *elmt);
    bool load_nodes(TiXmlNode *node);

    bool m_loaded;
    Type m_type;
};

#endif

