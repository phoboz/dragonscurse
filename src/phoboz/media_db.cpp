#include "SDL_mixer.h"
#include "phoboz/media_db.h"

struct MediaNode {
    enum Type { TypeSound };

    MediaNode(Type type) : m_key(m_keygen++), m_type(type), m_loaded(false) { }

    static int m_keygen;

    int m_key;
    Type m_type;
    bool m_loaded;
    std::string m_filename;
};

struct SoundNode : public MediaNode {
    SoundNode() : MediaNode(TypeSound) { }

    Mix_Chunk *m_sample;
};

int MediaNode::m_keygen = 1;

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
        if (strcmp(node->Value(), "sound") == 0) {
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

