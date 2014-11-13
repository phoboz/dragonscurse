#include "phoboz/ctrl.h"
#include "sub_menu.h"

SubMenu::SubMenu(Type type, MediaDB *media)
    : m_type(type),
      m_media(media),
      m_menu(0)
{
    m_menu = new Menu("Wonderfull_12", "icons.png", 0, media);
    if (m_menu) {
        m_menu->add_option("Back");
    }
}

SubMenu::~SubMenu()
{
    delete m_menu;
}

int SubMenu::move(int key)
{
    int result = -1;
    int input = get_input_keydown(key);

    if (input & PRESS_DOWN) {
        m_menu->advance_pointer(Menu::DirectionDown);
        m_media->play_sound("advance.wav");
    }
    else if (input & PRESS_UP) {
        m_menu->advance_pointer(Menu::DirectionUp);
        m_media->play_sound("advance.wav");
    }
    else if (input & PRESS_ENTER) {
        m_media->play_sound("select.wav");
        result = m_menu->get_option();
    }

    return result;
}

void SubMenu::draw(Surface *dest, int x, int y,
                   int clip_x, int clip_y, int clip_w, int clip_h)
{
    m_menu->draw(dest, x, y, clip_x, clip_y, clip_w, clip_h);
}

