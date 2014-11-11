#include <iostream>
#include <dirent.h>
#include "save_list.h"

SaveList::SaveList(MediaDB *media, WorldDB *db)
    : SubMenu(media, db->get_status()),
      m_db(db)
{
    DIR *dpdf;
    struct dirent *epdf;

    dpdf = opendir("./save/");
    if (dpdf) {
        while (epdf = readdir(dpdf)) {
            std::string filename = std::string(epdf->d_name);
            if (filename.find(".sav") != std::string::npos) {
                m_menu->add_option(filename.c_str(), new std::string(filename),
                                   0, 0);
            }
         }
    }
}

int SaveList::move(int key)
{
    int result = SubMenu::move(key);
    if (result > 0) {
        std::string *s = (std::string *) m_menu->get_data();
        m_db->restore(s->c_str(), m_media);
        delete s;
    }

    return result;
}

