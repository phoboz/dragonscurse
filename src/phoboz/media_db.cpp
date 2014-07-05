#include "SDL_mixer.h"
#include "phoboz/media_db.h"

struct MediaNode {
    enum Type { TypeSprite, TypeSound };

    MediaNode(Type type) :
        m_key(m_keygen++), m_ref(0), m_type(type), m_loaded(false) { }

    static int m_keygen;

    int m_key;
    int m_ref;
    Type m_type;
    bool m_loaded;
    std::string m_filename;
};

struct SpriteNode : public MediaNode {
    SpriteNode() : MediaNode(TypeSprite) { }

    int m_width;
    int m_height;
    int m_margin;
    int m_spacing;

    Sprite *m_sprite;
};

struct SoundNode : public MediaNode {
    SoundNode() : MediaNode(TypeSound) { }

    Mix_Chunk *m_sample;
};

int MediaNode::m_keygen = 1;

bool MediaDB::load_sprite_attributes(SpriteNode *sprite, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "filename") == 0) {
            sprite->m_filename = std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "width") == 0) {
            sprite->m_width = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "height") == 0) {
            sprite->m_height = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "margin") == 0) {
            sprite->m_margin = atoi(attr->Value());
        }
        else if (strcmp(attr->Name(), "spacing") == 0) {
            sprite->m_spacing = atoi(attr->Value());
        }
        else {
            result = false;
            break;
        }

        attr = attr->Next();
    }

    return result;
}

bool MediaDB::load_sound_attributes(SoundNode *sound, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "filename") == 0) {
            sound->m_filename = std::string(attr->Value());
        }
        else {
            result = false;
            break;
        }

        attr = attr->Next();
    }

    return result;
}

bool MediaDB::load_nodes(TiXmlNode *node)
{
    int result = true;

    if (node->Type() == TiXmlNode::TINYXML_ELEMENT) {
        if (strcmp(node->Value(), "sprite") == 0) {
            SpriteNode *sprite = new SpriteNode;
            result = load_sprite_attributes(sprite, node->ToElement());
            if (result) {
                m_media[sprite->m_filename] = sprite;
            }
        }
        else if (strcmp(node->Value(), "sound") == 0) {
            SoundNode *sound = new SoundNode;
            result = load_sound_attributes(sound, node->ToElement());
            if (result) {
                m_media[sound->m_filename] = sound;
            }
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

MediaDB::MediaDB(const char *name)
{
    TiXmlDocument doc(name);
    if (doc.LoadFile()) {
        load_nodes(&doc);
    }
}

bool MediaDB::load_sprite(SpriteNode *sprite)
{
    bool result = false;

    if (sprite->m_loaded) {
        result = true;
    }
    else {
        sprite->m_sprite = new Sprite(sprite->m_filename.c_str(),
                                      sprite->m_width, sprite->m_height,
                                      sprite->m_margin, sprite->m_spacing);
        if (sprite->m_sprite && sprite->m_sprite->get_loaded()) {
            sprite->m_loaded = true;
            result = true;
        }
    }

    return result;
}

Sprite* MediaDB::get_sprite(const char *filename)
{
    Sprite *result = 0;

    MediaNode *media = m_media[std::string(filename)];
    if (media->m_type == MediaNode::TypeSprite) {
        SpriteNode *sprite = (SpriteNode *) media;
        if (load_sprite(sprite)) {
            ++sprite->m_ref;
            result = sprite->m_sprite;
        }
    }

    return result;
}

SpriteNode* MediaDB::find_sprite(Sprite *find)
{
    SpriteNode *result = 0;

    for (std::map<std::string, MediaNode*>::const_iterator it = m_media.begin();
         it != m_media.end();
         ++it) {
        MediaNode *media = it->second;
        if (media->m_type == MediaNode::TypeSprite) {
            SpriteNode *sprite = (SpriteNode *) media;
            if (find == sprite->m_sprite) {
                result = sprite;
                break;
            }
        }
    }

    return result;
}

bool MediaDB::leave_sprite(Sprite *leave)
{
    bool result = false;

    SpriteNode *sprite = find_sprite(leave);
    if (--sprite->m_ref == 0) {
        delete sprite->m_sprite;
        sprite->m_loaded = false;
        result = true;
    }

    return result;
}

bool MediaDB::load_sound(SoundNode *sound)
{
    bool result = false;

    if (sound->m_loaded) {
        result = true;
    }
    else {
        sound->m_sample = Mix_LoadWAV(sound->m_filename.c_str());
        if (sound->m_sample) {
            sound->m_loaded = true;
            result = true;
        }
    }

    return result;
}

bool MediaDB::play_sound(const char *filename)
{
    bool result = false;

    MediaNode *media = m_media[std::string(filename)];
    if (media->m_type == MediaNode::TypeSound) {
        SoundNode *sound = (SoundNode *) media;
        if (load_sound(sound)) {
            if(Mix_PlayChannel(-1, sound->m_sample, 0) != -1) {
                result = true;
            }
        }
    }

    return result;
}

