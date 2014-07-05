#ifndef _Area_H
#define _Area_H

#include <string>
#include "phoboz/timer.h"
#include "object.h"
#include "world_db.h"

class Actor;
class Curse;
class World;

class Area : public Object {
public:
    enum Type { TypeWarp, TypeTravel, TypeCurse, TypeMorph, TypeUser };
    enum State { StateLocked, StateClosed, StateOpening, StateOpen };

    Area(const char *name, MediaDB *media,
         const char *type, int x, int y, int w, int h);
    Area(Curse *curse);

    virtual void world_initialize(World *world);

    bool is_over(Actor *actor);

    const char* get_name() const { return m_name.c_str(); }
    Type get_type() const { return m_type; }
    int get_x1() const { return m_x; }
    int get_y1() const { return m_y; }
    int get_x2() const { return m_x + m_w; }
    int get_y2() const { return m_y + m_h; }
    int get_sx() const { return get_attribute("start_x"); }
    int get_sy() const { return get_attribute("start_y"); }
    bool is_locked() const { return m_state == StateLocked; }
    bool is_open() const { return m_state == StateOpen; }
    const char* get_data() const { return m_data.c_str(); }

    virtual bool get_visible(Map *map, int clip_x, int clip_y,
                             int clip_w, int clip_h) const { return true; }

    virtual void move(Map *map);
    bool move_unlock(World *world);
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    std::string m_name;
    Type m_type;
    int m_w, m_h;
    std::string m_data;
    int m_world_key;
    State m_state;
    Timer m_open_timer;
    Timer m_anim_timer;
};

#endif

