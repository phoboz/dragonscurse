#ifndef _MediaDB_H
#define _MediaDB_H

#include <string>
#include <map>
#include "tinyxml.h"
#include "phoboz/sprite.h"

struct MediaNode;
struct SpriteNode;
struct SoundNode;

class MediaDB {
public:
    MediaDB(const char *name);

    Sprite* get_sprite(const char *filename);
    bool leave_sprite(Sprite *leave);

    bool play_sound(const char *filename);

private:
    bool load_sprite_attributes(SpriteNode *sprite, TiXmlElement *elmt);
    bool load_sound_attributes(SoundNode *sound, TiXmlElement *elmt);
    bool load_nodes(TiXmlNode *node);

    bool load_sprite(SpriteNode *sprite);
    SpriteNode* find_sprite(Sprite *find);

    bool load_sound(SoundNode *sound);

    std::map<std::string, MediaNode*> m_media;
};

#endif

