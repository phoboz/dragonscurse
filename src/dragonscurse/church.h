#ifndef _Church_H
#define _Church_H

#include "room.h"

class Church : public Room {
public:
    Church(const char *image, MediaDB *media, int sx, int sy);

    virtual Area* move();
};

#endif

