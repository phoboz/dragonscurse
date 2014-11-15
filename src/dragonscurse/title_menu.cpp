#include "phoboz/ctrl.h"
#include "title_menu.h"

int TitleMenu::s_last_option = 0;

TitleMenu::TitleMenu(MediaDB *media)
    : m_media(media)
{
    m_menu = new Menu("Wonderfull_18", "icons.png", 0, media);
    if (m_menu) {
        m_menu->add_option("New Game");
        m_menu->add_option("Load Game");
        m_menu->add_option("Fullscreen/Window mode");
        m_menu->add_option("Quit");
        if (s_last_option) {
            m_menu->set_option(s_last_option);
        }
    }

    media->play_music("seaside.ogg");
}

TitleMenu::~TitleMenu()
{
    s_last_option = m_menu->get_option();
    delete m_menu;
}

TitleMenu::Option TitleMenu::move(int key)
{
    Option option = OptionNone;

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
        option = (Option) m_menu->get_option();
    }

    return option;
}

void TitleMenu::draw(Surface *dest, int x, int y,
                     int clip_x, int clip_y, int clip_w, int clip_h)
{
    m_menu->draw(dest, x, y, clip_x, clip_y, clip_w, clip_h);
}

