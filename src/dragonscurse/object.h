#ifndef _Object_H
#define _Object_H

#include <string>
#include <map>
#include "tinyxml.h"
#include "phoboz/sprite.h"
#include "phoboz/map.h"

class Object {
public:
    enum Type { TypePlayer, TypeEnemy, TypeBullet, TypeArea };
    enum Direction { Keep, Right, Left };
    enum VerticalDirection { VerticalNone, VerticalUp, VerticalDown };
    enum HorizontalDirection { HorizontalNone,
                               HorizontalForward,
                               HorizontalBackward };

    Object(Type type, int x = 0, int y = 0)
        : m_x(x), m_y(y), m_dx(0), m_dy(0), m_frame(0),
          m_dir(Right), m_loaded(false), m_type(type), m_always_visible(false),
          m_xref(0), m_yref(0) { }
    Object(Type type, int x, int y, Direction dir)
        : m_x(x), m_y(y), m_dx(0), m_dy(0), m_frame(0),
          m_dir(dir), m_loaded(false), m_type(type), m_always_visible(false),
          m_xref(0), m_yref(0) { }
    ~Object();
    bool load(const char *fn);
    bool get_loaded() const { return m_loaded; }
    virtual void initialize() { }
    Type get_type() const { return m_type; }
    int get_x() const { return m_x; }
    int get_y() const { return m_y; }
    int get_frame() const { return m_frame; }
    const Sprite* get_sprite() const { return m_spr; }
    int get_image_width() const { return m_spr->get_image_width(); }
    int get_image_height() const { return m_spr->get_image_height(); }
    void set_x(int value) { m_x = value; }
    void set_y(int value) { m_y = value; }
    void set_reference(int x, int y) { m_xref = x; m_yref = y; }
    int  get_attribute(const char *name) const;
    void set_attribute(const char *name, int value) {
        m_attributes[std::string(name)] = value;
    }
    virtual bool get_visible(Map *map, int clip_x, int clip_y,
                             int clip_w, int clip_h) const;
    virtual bool check_collision(Object *object) {
        return m_spr->check_collision(m_frame, m_x, m_y,
                                      object->m_spr, object->m_frame,
                                      object->m_x, object->m_y);
    }
    virtual void move(Map *map) = 0;
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h) {
        m_spr->draw(dest,
                    m_x - map->get_x() + clip_x,
                    m_y - map->get_y() + clip_y,
                    m_frame,
                    clip_x, clip_y, clip_w, clip_h);
    }

protected:
    const char* get_string(const char *name) const;

    bool check_collision(int x, int y, Map *map, int id);
    bool check_below(Map *map, int id = 0);
    bool check_ahead(Map *map, int id = 0);
    bool check_behind(Map *map, int id = 0);
    bool check_above(Map *map, int id = 0);

    void set_always_visible(bool value) { m_always_visible = value; }

    std::map<std::string, int> m_attributes;
    std::map<std::string, std::string> m_strings;

    int m_x, m_y;
    int m_dx, m_dy;
    int m_frame;
    Direction m_dir;
    int m_xref, m_yref;

private:
    bool load_object_attributes(TiXmlElement *elmt);
    void load_strings(TiXmlElement *elmt);
    void load_attributes(TiXmlElement *elmt);
    bool load_nodes(TiXmlNode *node);

    bool m_loaded;
    Type m_type;
    bool m_always_visible;
    Sprite *m_spr;
    std::string m_obj_type;
};

#endif

