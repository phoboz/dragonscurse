#include <iostream>
#include <dirent.h>
#include "save_list.h"

SaveList::SaveList(MediaDB *media)
    : SubMenu(TypeSave, media)
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

const char* SaveList::get_string() const
{
    std::string *s = (std::string *) m_menu->get_data();
    return s->c_str();
}

