#ifndef _Area_H
#define _Area_H

#include <string>
#include "phoboz/timer.h"
#include "object.h"

class Actor;
class Item;
class Curse;
class World;
struct EventArea;

class Area : public Object {
public:
    enum Type {
        TypeWarp,
        TypeMap,
        TypeCurse,
        TypeMorph,
        TypeUser
    };

    enum State {
        StateLocked,
        StateClosed,
        StateOpening,
        StateOpen,
        StateInactive
    };

    Area(const char *name, MediaDB *media,
         const char *type, int x, int y, int w, int h);
    Area(Curse *curse);
    Area(const char *destination, int sx, int sy);
    Area(EventArea *area, MediaDB *media);

    virtual void world_initialize(World *world);

    const char* get_name() const { return m_name.c_str(); }
    Type get_type() const { return m_type; }
    int get_x1() const { return m_x; }
    int get_y1() const { return m_y; }
    int get_x2() const { return m_x + m_w; }
    int get_y2() const { return m_y + m_h; }
    int get_sx() const { return m_sx; }
    int get_sy() const { return m_sy; }
    const char* get_music() const { return get_string("music"); }
    bool is_over(Actor *actor);
    bool is_locked() const { return m_state == StateLocked; }
    bool is_open() const { return m_state == StateOpen; }
    const char* get_data() const { return m_data.c_str(); }

    virtual bool get_visible(Map *map, int clip_x, int clip_y,
                             int clip_w, int clip_h) const { return true; }

    virtual void move(Map *map);
    bool unlock(World *world, Item *item);
    virtual void draw(Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

    bool map_to_world(World *world);

private:
    std::string m_name;
    Type m_type;
    int m_w, m_h;
    int m_sx, m_sy;
    std::string m_data;
    int m_world_key;
    int m_once;
    State m_state;
    Timer m_open_timer;
    Timer m_anim_timer;
};

#endif

