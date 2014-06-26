#include <iostream>
#include <vector>
#include <string>
#include "Tmx/Tmx.h"
#include "object_factory.h"
#include "player.h"
#include "monster.h"
#include "item.h"
#include "curse.h"
#include "statusbar.h"
#include "world.h"

World::World(Map *map, WorldDB *db, bool load_music)
    : m_map(map), m_db(db)
{
    std::string music_fn;

    // Load attributes
    m_bg_color = m_map->get_numeric_property("bg_color");

    // Load music
    if (load_music) {
        music_fn = m_map->get_literal_property("music");
        if (music_fn.empty()) {
            m_music = 0;
        }
        else {
            m_music = Mix_LoadMUS(music_fn.c_str());
        }
    }
    else {
        m_music = 0;
    }

    int num_groups = map->get_num_object_groups();
    for (int object_group = 0; object_group < num_groups; object_group++) {
        const Tmx::ObjectGroup *group = map->get_object_group(object_group);
        std::string name = group->GetName();
        int num_objects = group->GetNumObjects();

        for (int i = 0; i < num_objects; i++) {
            const Tmx::Object *obj = group->GetObject(i);
            const Tmx::PropertySet prop = obj->GetProperties();
            std::string dirname =
                prop.GetLiteralProperty(std::string("direction"));
            Object *object = ObjectFactory::create_object(
                                 obj->GetName().c_str(),
                                 obj->GetType().c_str(),
                                 obj->GetX(),
                                 obj->GetY(),
                                 obj->GetWidth(),
                                 obj->GetHeight(),
                                 prop);
            if (object) {
                object->world_initialize(this);
                m_objects.push_back(object);
            }
            else {
                std::cerr << "Warning - Unable to load object: " << i
                          << std::endl;
            }
        }
    }
}

bool World::start()
{
    bool status;

    if (m_music) {

        // Play music infinite looping
        if(Mix_PlayMusic(m_music, -1) == -1) {
            status = false;
        }
        else {
            status = true;
        }
    }
    else {
        status = true;
    }

    return status;
}

void World::end()
{
    if (m_music) {
        Mix_HaltMusic();
    }
}

Area* World::move(Player *player,
                  int clip_x, int clip_y, int clip_w, int clip_h)
{
    Area *result = 0;

    player->move(m_map);
    int window_width = clip_w - clip_x;
    int window_height = clip_h - clip_y;
    int map_x = player->get_x() - window_width / 2;
    int map_y = player->get_y() - window_height / 2;
    if (map_x < 0) {
        map_x = 0;
    }
    if (map_y < 0) {
        map_y = 0;
    }
    m_map->set_x(map_x, 640);
    m_map->set_y(map_y, 480 - Statusbar::get_height());

    std::vector<Object*> perished;

    for (std::list<Object*>::iterator it = m_objects.begin();
         it != m_objects.end();
         ++it) {
        Object *object = *it;

        if (object->get_visible(m_map, clip_x, clip_y, clip_w, clip_h)) {
            Object::Type object_type = object->get_type();

            // Handle area objects
            if (object_type == Object::TypeArea) {
                Area *area = (Area *) object;

                if (area->is_locked()) {

                    // Check if the player has the key
                    Item *item = player->check_item(area->get_lock_type());
                    if (item) {
                        if (area->move_unlock(this)) {
                            player->remove_item(item);
                        }
                    }
                }
                else {
                    area->move(m_map);

                    if (area->inside(player)) {
                        result = area;
                    }
                }
            }

            // Handle monster object
            else if (object_type == Object::TypeMonster) {
                Monster *monster = (Monster *) object;

                monster->move(m_map);
                monster->set_reference(player->get_front(), player->get_y());
                if (player->check_collision(monster)) {
                    if (!monster->get_invisible()) {
                        player->set_hit(monster);
                    }
                }
                if (player->attack_actor(monster)) {
                    monster->set_hit(player);
                }
                if (monster->get_hit() == Actor::HitPerished) {
                    perished.push_back(*it);
                }
            }

            // Handle item objects
            else if (object_type == Object::TypeItem) {
                Item *item = (Item *) object;

                item->move(m_map);

                // Check if player picked up item
                if (player->check_collision(item)) {
                    player->aquire_item(item);
                    item->aquire(this);
                    item->set_reused(true);
                    perished.push_back(*it);
                }
            }

            // Handle curse objects
            else if (object_type == Object::TypeCurse) {
                Curse *curse = (Curse *) object;

                curse->move(m_map);
            }
        }
    }

    // Remove all perished objects
    for (int i = 0; i < perished.size(); i++) {

        // If monster drop object
        if (perished[i]->get_type() == Object::TypeMonster) {
            Monster *monster = (Monster *) perished[i];
            Object *released_object = monster->release_object();
            if (released_object) {
                released_object->set_x(monster->get_x());
                released_object->set_y(monster->get_y());
                m_objects.push_back(released_object);
            }
        }
        m_objects.remove(perished[i]);

        if (!perished[i]->get_reused()) {
            delete perished[i];
        }
    }

    return result;
}

void World::draw(SDL_Surface *dest, Player *player,
                 int clip_x, int clip_y, int clip_w, int clip_h)
{
    // Draw background
    SDL_Rect rect;
    rect.x = clip_x;
    rect.y = clip_y;
    rect.w = clip_w;
    rect.h = clip_h;

    SDL_FillRect(dest, &rect, m_bg_color);

    int num_layers = m_map->get_num_layers();

    if (num_layers > 0) {
        m_map->draw_layer(dest, clip_x, clip_y, clip_w, clip_h, 0);
    }

    // Draw objects
    for (std::list<Object*>::iterator it = m_objects.begin();
         it != m_objects.end();
         ++it) {
        Object *object = *it;
        object->draw(dest, m_map, clip_x, clip_y, clip_w, clip_h);
    }

    player->draw(dest, m_map, clip_x, clip_y, clip_w, clip_h);

    if (num_layers > 1) {
        m_map->draw_layer(dest, clip_x, clip_y, clip_w, clip_h, 1);
    }

}

