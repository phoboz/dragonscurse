#include "phoboz/ctrl.h"
#include "main_menu.h"

int MainMenu::s_last_option = 0;

MainMenu::MainMenu(MediaDB *media)
    : m_media(media)
{
    m_menu = new Menu("Wonderfull_18", "icons.png", 0, media);
    if (m_menu) {
        m_menu->add_option("New Game");
        m_menu->add_option("Continue");
        m_menu->add_option("Key List");
        m_menu->add_option("Arm List");
        m_menu->add_option("Shield List");
        m_menu->add_option("Armour List");
        m_menu->add_option("Quit");
        if (s_last_option) {
            m_menu->set_option(s_last_option);
        }
    }
}

MainMenu::~MainMenu()
{
    s_last_option = m_menu->get_option();
    delete m_menu;
}

bool MainMenu::check_menu(int key)
{
    bool result = false;

    int input = get_input_keydown(key);
    if (input & PRESS_ESC) {
        result = true;
    }

    return result;
}

MainMenu::Option MainMenu::move(int key)
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
    else if (input & PRESS_ESC) {
        option = OptionContinue;
    }

    return option;
}

void MainMenu::draw(SDL_Surface *dest, int x, int y,
                    int clip_x, int clip_y, int clip_w, int clip_h)
{
    m_menu->draw(dest, x, y, clip_x, clip_y, clip_w, clip_h);
}

