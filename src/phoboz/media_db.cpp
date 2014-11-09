#include "SDL_mixer.h"
#include "phoboz/text.h"
#include "phoboz/media_db.h"

struct MediaNode {
    enum Type { TypeSprite, TypeMap, TypeFont, TypeSound, TypeMusic };

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

struct MapNode : public MediaNode {
    MapNode() : MediaNode(TypeMap) { }

    Map *m_map;
};

struct FontNode : public MediaNode {
    FontNode() : MediaNode(TypeFont) { }

    int m_size;
    std::string m_name;
    TTF_Font *m_font;
};

struct SoundNode : public MediaNode {
    SoundNode() : MediaNode(TypeSound) { }

    Mix_Chunk *m_sample;
};

struct MusicNode : public MediaNode {
    MusicNode() : MediaNode(TypeMusic) { }

    Mix_Music *m_music;
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

bool MediaDB::load_map_attributes(MapNode *map, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "filename") == 0) {
            map->m_filename = std::string(attr->Value());
        }
        else {
            result = false;
            break;
        }

        attr = attr->Next();
    }

    return result;
}

bool MediaDB::load_font_attributes(FontNode *font, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "name") == 0) {
            font->m_name = std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "filename") == 0) {
            font->m_filename = std::string(attr->Value());
        }
        else if (strcmp(attr->Name(), "size") == 0) {
            font->m_size = atoi(attr->Value());
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

bool MediaDB::load_music_attributes(MusicNode *music, TiXmlElement *elmt)
{
    bool result = true;

    TiXmlAttribute *attr = elmt->FirstAttribute();
    while (attr) {
        if (strcmp(attr->Name(), "filename") == 0) {
            music->m_filename = std::string(attr->Value());
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
        else if (strcmp(node->Value(), "map") == 0) {
            MapNode *map = new MapNode;
            result = load_map_attributes(map, node->ToElement());
            if (result) {
                m_media[map->m_filename] = map;
            }
        }
        else if (strcmp(node->Value(), "font") == 0) {
            FontNode *font = new FontNode;
            result = load_font_attributes(font, node->ToElement());
            if (result) {
                m_media[font->m_name] = font;
            }
        }
        else if (strcmp(node->Value(), "sound") == 0) {
            SoundNode *sound = new SoundNode;
            result = load_sound_attributes(sound, node->ToElement());
            if (result) {
                m_media[sound->m_filename] = sound;
            }
        }
        else if (strcmp(node->Value(), "music") == 0) {
            MusicNode *music = new MusicNode;
            result = load_music_attributes(music, node->ToElement());
            if (result) {
                m_media[music->m_filename] = music;
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
    : m_mus_filename(""),
      m_sprite_prefix("./sprites/"),
      m_map_prefix("./maps/"),
      m_font_prefix("./fonts/"),
      m_sound_prefix("./sounds/"),
      m_music_prefix("./music/")
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
        std::string pathname = m_sprite_prefix + sprite->m_filename;
        sprite->m_sprite = new Sprite(pathname.c_str(),
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

SpriteNode* MediaDB::find_sprite(const Sprite *find)
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

void MediaDB::reference_sprite(const Sprite *spr)
{
    SpriteNode *sprite = find_sprite(spr);
    ++sprite->m_ref;
}

bool MediaDB::leave_sprite(Sprite *spr)
{
    bool result = false;

    SpriteNode *sprite = find_sprite(spr);
    if (--sprite->m_ref == 0) {
        delete sprite->m_sprite;
        sprite->m_loaded = false;
        result = true;
    }

    return result;
}

bool MediaDB::load_map(MapNode *map)
{
    bool result = false;

    if (map->m_loaded) {
        result = true;
    }
    else {
        std::string pathname = m_map_prefix + map->m_filename;
        Tmx::Map *tmx = new Tmx::Map();
        tmx->ParseFile(pathname.c_str());
        map->m_map = new Map(tmx, m_map_prefix.c_str());
        if (map->m_map && map->m_map->get_loaded()) {
            map->m_loaded = true;
            result = true;
        }
    }

    return result;
}

Map* MediaDB::get_map(const char *filename)
{
    Map *result = 0;

    MediaNode *media = m_media[std::string(filename)];
    if (media->m_type == MediaNode::TypeMap) {
        MapNode *map = (MapNode *) media;
        if (load_map(map)) {
            ++map->m_ref;
            result = map->m_map;
        }
    }

    return result;
}

bool MediaDB::load_font(FontNode *font)
{
    bool result = false;

    if (font->m_loaded) {
        result = true;
    }
    else {
        std::string pathname = m_font_prefix + font->m_filename;
        font->m_font = Text::load_font(pathname.c_str(), font->m_size);
        if (font->m_font) {
            font->m_loaded = true;
            result = true;
        }
    }

    return result;
}

TTF_Font* MediaDB::get_font(const char *fontname)
{
    TTF_Font *result = 0;

    MediaNode *media = m_media[std::string(fontname)];
    if (media->m_type == MediaNode::TypeFont) {
        FontNode *font = (FontNode *) media;
        if (load_font(font)) {
            ++font->m_ref;
            result = font->m_font;
        }
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
        std::string pathname = m_sound_prefix + sound->m_filename;
        sound->m_sample = Mix_LoadWAV(pathname.c_str());
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

bool MediaDB::load_music(MusicNode *music)
{
    bool result = false;

    if (music->m_loaded) {
        result = true;
    }
    else {
        std::string pathname = m_music_prefix + music->m_filename;
        music->m_music = Mix_LoadMUS(pathname.c_str());
        if (music->m_music) {
            music->m_loaded = true;
            result = true;
        }
    }

    return result;
}

void MediaDB::unload_music(const char *filename)
{
    MediaNode *media = m_media[std::string(filename)];
    if (media->m_type == MediaNode::TypeMusic) {
        MusicNode *music = (MusicNode *) media;
        if (music->m_loaded) {
            MusicNode *music = (MusicNode *) media;
            Mix_FreeMusic(music->m_music);
            music->m_loaded = false;
        }
    }
}

bool MediaDB::play_music(const char *filename)
{
    bool result = false;

    if (m_mus_filename == std::string(filename)) {
        result = true;
    }
    else {
        if (m_mus_filename != std::string("")) {
            Mix_HaltMusic();
            unload_music(m_mus_filename.c_str());
        }

        MediaNode *media = m_media[std::string(filename)];
        if (media->m_type == MediaNode::TypeMusic) {
            MusicNode *music = (MusicNode *) media;
            if (load_music(music)) {
                if(Mix_PlayMusic(music->m_music, -1) != -1) {
                    m_mus_filename = music->m_filename;
                    result = true;
                }
            }
        }
    }

    return result;
}

