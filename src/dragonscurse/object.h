#ifndef _Object_H
#define _Object_H

#include <string>
#include <vector>
#include <map>
#include "tinyxml.h"
#include "phoboz/media_db.h"
#include "phoboz/map.h"

class World;

// Hidden
struct CollisionParts;

class Object {
public:
    enum Type {
        TypeNone,
        TypePlayer,
        TypeMonster,
        TypeBullet,
        TypeItem,
        TypeCollectable,
        TypeCurse,
        TypeMorph,
        TypeArea,
        TypeChest
    };

    enum Direction { Keep, Right, Left };

    enum VerticalDirection { VerticalNone, VerticalUp, VerticalDown };

    enum HorizontalDirection {
        HorizontalNone,
        HorizontalForward,
        HorizontalBackward
    };

    enum AnimDirection { AnimUp, AnimDown };

    Object(Type type, int x = 0, int y = 0)
        : m_x(x), m_y(y), m_dx(0), m_dy(0), m_frame(0),
          m_dir(Right), m_loaded(false), m_type(type), m_always_visible(false),
          m_reused(false),
          m_xref(0), m_yref(0) { }
    Object(Type type, int x, int y, Direction dir)
        : m_x(x), m_y(y), m_dx(0), m_dy(0), m_frame(0),
          m_dir(dir), m_loaded(false), m_type(type), m_always_visible(false),
          m_reused(false),
          m_xref(0), m_yref(0) { }
    ~Object();
    bool load(const char *fn, MediaDB *media);
    bool get_loaded() const { return m_loaded; }
    virtual void initialize() { }

    // Only called when objects are initialized from world
    virtual void world_initialize(World *world) { }

    Type get_type() const { return m_type; }
    int get_x() const { return m_x; }
    int get_y() const { return m_y; }
    Direction get_dir() const { return m_dir; }
    int get_frame() const { return m_frame; }
    const Sprite* get_sprite() const { return m_spr; }
    int get_image_width() const { return m_spr->get_image_width(); }
    int get_image_height() const { return m_spr->get_image_height(); }
    virtual Direction get_reference() const;
    int get_front() const;
    int get_bottom() const;
    bool get_reused() { return m_reused; }

    void set_x(int value) { m_x = value; }
    void set_y(int value) { m_y = value; }
    void set_reference(int x, int y) { m_xref = x; m_yref = y; }

    void set_reused(bool reused) { m_reused = reused; }

    const char* get_filename() { return m_fn.c_str(); }
    const char* get_name() { return m_name.c_str(); }
    int  get_attribute(const char *name) const;
    void set_attribute(const char *name, int value) {
        m_attributes[std::string(name)] = value;
    }
    void set_string(const char *name, const char *value) {
        m_strings[std::string(name)] = std::string(value);
    }
    virtual bool get_visible(Map *map, int clip_x, int clip_y,
                             int clip_w, int clip_h) const;
    virtual bool check_collision(Object *object) const {
        return m_spr->check_collision(m_frame, m_x, m_y,
                                      object->m_spr, object->m_frame,
                                      object->m_x, object->m_y);
    }
    bool check_weak_collision(Object *object) const;
    bool check_weak_collision(Object *object,
                              int start_x1, int start_y1,
                              int end_x1, int end_y1) const;
    bool check_shielded_collision(Object *object) const;

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

    bool check_collision(int x, int y, Map *map, int start = 0, int end = 0);
    bool check_center(Map *map, int start = 0, int end = 0);
    bool check_below(Map *map, int start = 0, int end = 0);
    int check_below(Map *map, int len, int start, int end);
    bool check_ahead(Map *map, int start = 0, int end = 0);
    int check_ahead(Map *map, int len, int start, int end);
    bool check_behind(Map *map, int start = 0, int end = 0);
    bool check_above(Map *map, int start = 0, int end = 0);
    int check_above(Map *map, int len, int start = 0, int end = 0);

    void set_always_visible(bool value) { m_always_visible = value; }

    std::map<std::string, int> m_attributes;
    std::map<std::string, std::string> m_strings;
    std::vector<CollisionParts*> m_weak_parts;
    std::vector<CollisionParts*> m_shielded_parts;

    int m_x, m_y;
    int m_dx, m_dy;
    int m_frame;
    Direction m_dir;
    int m_xref, m_yref;
    MediaDB *m_media;

private:
    bool load_object_attributes(TiXmlElement *elmt);
    void load_strings(TiXmlElement *elmt);
    void load_attributes(TiXmlElement *elmt);
    bool load_nodes(TiXmlNode *node);
    CollisionParts* find_collision_parts(std::vector<CollisionParts*> v) const;

    std::string m_fn;
    std::string m_name;
    bool m_loaded;
    Type m_type;
    bool m_always_visible;
    bool m_reused;
    Sprite *m_spr;

};

#endif

