#ifndef _Object_H
#define _Object_H

#include <string>
#include <map>
#include "tinyxml.h"
#include "phoboz/sprite.h"
#include "phoboz/map.h"

class Object {
public:
    enum Type { Player, Enemy };
    enum AnimDirection { AnimUp, AnimDown };
    enum Direction { Keep, Right, Left };
    enum Action { Stand, Walk, Fall, Jump, Crouch, Ability };

    Object(Type type)
        : m_x(0), m_y(0), m_dx(0), m_dy(0),
          m_anim_dir(AnimUp), m_counter(0), m_frame(0),
          m_dir(Right), m_action(Stand),
          m_loaded(false), m_type(type) { }
    ~Object();
    bool load(const char *fn);
    bool get_loaded() const { return m_loaded; }
    int get_x() const { return m_x; }
    int get_y() const { return m_y; }
    void draw(SDL_Surface *dest, Map *map,
              int clip_x, int clip_y, int clip_w, int clip_h) const {
        m_spr->draw(dest, m_x - map->get_x(), m_y - map->get_y(), m_frame,
                    clip_x, clip_y, clip_w, clip_h);
    }
    virtual void move(Map *map) = 0;

protected:
    int  get_attribute(const char *name) {
        return m_attributes[std::string(name)];
    }

    bool check_collision(int x, int y, Map *map);
    bool check_below(Map *map);
    bool check_ahead(Map *map);
    bool check_above(Map *map);

    bool set_dir(Direction dir);
    bool set_stand();
    void set_jump();
    void set_crouch();
    void animate_walk();

    std::map<std::string, int> m_attributes;
    int m_x, m_y;
    int m_dx, m_dy;
    AnimDirection m_anim_dir;
    int m_counter;
    int m_frame;
    Direction m_dir;
    Action m_action;
    Sprite *m_spr;

private:
    bool load_object_attributes(TiXmlElement *elmt);
    void load_extra_attributes(TiXmlElement *elmt);
    bool load_nodes(TiXmlNode *node);

    bool m_loaded;
    Type m_type;
};

#endif

