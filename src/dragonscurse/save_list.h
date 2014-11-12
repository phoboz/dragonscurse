#ifndef _SaveList_H
#define _SaveList_H

#include "world_db.h"
#include "sub_menu.h"

class SaveList : public SubMenu {
public:
    SaveList(MediaDB *media);

    const char* get_string() const;

private:
    WorldDB **m_db;
};

#endif

