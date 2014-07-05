#ifndef _MediaDB_H
#define _MediaDB_H

#include <string>
#include <map>
#include "tinyxml.h"

struct SoundNode;
struct MediaNode;

class MediaDB {
public:
    MediaDB(const char *name);

    bool play_sound(const char *filename);

private:
    bool load_sound_attributes(SoundNode *sound, TiXmlElement *elmt);
    bool load_nodes(TiXmlNode *node);

    bool load_sound(SoundNode *sound);

    std::map<std::string, MediaNode*> m_media;
};

#endif

