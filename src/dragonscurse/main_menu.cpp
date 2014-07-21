#include "phoboz/ctrl.h"
#include "main_menu.h"

MainMenu::MainMenu(MediaDB *media, Status *status)
    : m_media(media),
      m_status(status)
{
    m_menu = new Menu("Wonderfull_18", "icons.png", 0, media);
    if (m_menu) {
        m_menu->add_option("Continue");
        m_menu->add_option("Status");
        m_menu->add_option("Quit");
    }
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

bool MainMenu::move(int key)
{
    bool result = false;
    void *data = 0;

    int input = get_input_keydown(key);
    if (input & PRESS_DOWN) {
        data = m_menu->advance_pointer(Menu::DirectionDown);
        m_media->play_sound("advance.wav");
    }
    else if (input & PRESS_UP) {
        data = m_menu->advance_pointer(Menu::DirectionUp);
        m_media->play_sound("advance.wav");
    }
    else if (input & PRESS_ENTER) {
        m_media->play_sound("select.wav");
        int option = m_menu->get_option();
        switch(option) {
            case 1:
                m_status->show();
                break;

            case 2:
                exit(0);
                break;

            default:
                result = true;
                break;
        }
    }

    return result;
}

void MainMenu::draw(SDL_Surface *dest, int x, int y,
                    int clip_x, int clip_y, int clip_w, int clip_h)
{
    m_menu->draw(dest, x, y, clip_x, clip_y, clip_w, clip_h);
}

