#ifndef _MediaDB_H
#define _MediaDB_H

#include <string>
#include <map>
#include "tinyxml.h"
#include "phoboz/sprite.h"
#include "phoboz/font.h"
#include "phoboz/map.h"

// Hidden
struct MediaNode;
struct SpriteNode;
struct MapNode;
struct FontNode;
struct SoundNode;
struct MusicNode;

class MediaDB {
public:
    MediaDB(const char *name);

    Sprite* get_sprite(const char *filename);
    void reference_sprite(const Sprite *spr);
    bool leave_sprite(Sprite *spr);
    Map* get_map(const char *filename);
    bool leave_map(Map *map);
    Font* get_font(const char *fontname);
    bool play_sound(const char *filename);
    bool play_music(const char *filename);

private:
    bool load_block_attributes(std::string &prefix, TiXmlElement *elmt);
    bool load_sprite_attributes(SpriteNode *sprite, TiXmlElement *elmt);
    bool load_map_attributes(MapNode *map, TiXmlElement *elmt);
    bool load_font_attributes(FontNode *font, TiXmlElement *elmt);
    bool load_sound_attributes(SoundNode *sound, TiXmlElement *elmt);
    bool load_music_attributes(MusicNode *music, TiXmlElement *elmt);
    bool load_nodes(TiXmlNode *node);

    bool load_sprite(SpriteNode *sprite);
    SpriteNode* find_sprite(const Sprite *find);
    bool load_map(MapNode *map);
    MapNode* find_map(const Map *find);
    bool load_font(FontNode *font);
    bool load_sound(SoundNode *sound);
    bool load_music(MusicNode *music);
    void unload_music(const char *filename);

    std::string m_sprite_prefix;
    std::string m_map_prefix;
    std::string m_font_prefix;
    std::string m_sound_prefix;
    std::string m_music_prefix;

    std::map<std::string, MediaNode*> m_media;
    std::string m_mus_filename;
};

#endif

