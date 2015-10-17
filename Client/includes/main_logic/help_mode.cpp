
#include "help_mode.h"
#include "../video/window.h"
#include "../gui/click.h"
#include "../gui/text_button.h"
#include "game_logic.h"
#include "../gui/text.h"
#include "main_menu_mode.h"
#include <cstdio>

namespace main_logic
{

Help_mode::Help_mode(utility::Configuration * config):
    main_config(config),
    change_mode(false)
{
    main_background.change_image(config->find_string("main_background").c_str());

    gui::Text_button * return_button = new gui::Text_button(main_config , "Return" , 100,  600);
    auto return_button_function = [this]()
    {
        Game_logic::set_current_mode(new Main_menu_mode(this->main_config));
    };
    return_button->init_function(return_button_function);
    main_gui.add_element(return_button);

    gui::Text * help_text = new gui::Text(main_config,"Open the groups of words to practice them", 100, 100, 48, SDL_Color {235,235,235});
    gui::Text * help_text_second = new gui::Text(main_config,"Try to guess all words correctly as fast as you can", 100, 200, 48, SDL_Color {235,235,235});
    gui::Text * help_text_third = new gui::Text(main_config,"As more time is spent on a word, more letters will open up", 100, 300, 48, SDL_Color {235,235,235});

    main_gui.add_element(help_text);
    main_gui.add_element(help_text_second);
    main_gui.add_element(help_text_third);

}

bool Help_mode::run()
{
    if(handle_input()==false)
    {
        return false;
    }
    else if(change_mode==true)
    {
        return true;
    }
    video::Video_subsystem::reload();

    //update
    main_gui.update();

    //show
    main_background.show();
    main_gui.show();

    video::Video_subsystem::update_screen();

    return true;
}

bool Help_mode::handle_input()
{
    gui::Click click;
    click.set_clicked(false);
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            return false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            click.set_clicked(false);
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                click.set_location(event.button.x,event.button.y);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            click.set_clicked(true);
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                click.set_location(event.button.x,event.button.y);
            }
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_r:
                break;
            case SDLK_ESCAPE:
                main_logic::Game_logic::set_current_mode( new Main_menu_mode (main_config) );
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEWHEEL:
            break;
        default:
            break;
        }
    }
    const Uint8 * key_strokes = SDL_GetKeyboardState(nullptr);
    if((key_strokes[SDL_SCANCODE_RALT]||key_strokes[SDL_SCANCODE_LALT])&&key_strokes[SDL_SCANCODE_TAB])
    {
        video::Video_subsystem::minimize();
    }



    return true;
}

}//end of main_logic namespace
