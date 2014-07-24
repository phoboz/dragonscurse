#ifndef _KeyList_H
#define _KeyList_H

#include "item_list.h"

class KeyList : public ItemList {
public:
    KeyList(MediaDB *media, Status *status)
        : ItemList(media, status, Item::TypeKey) { }
};

#endif

