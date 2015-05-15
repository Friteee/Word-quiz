
#include "group_selection_mode.h"
#include "game_logic.h"
#include "../gui/button.h"
#include "../gui/click.h"
#include "../audio/music.h"



namespace main_logic
{

/**
 * Group_selection's input handler
 */

bool Group_selection_mode::handle_input()
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
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_q:
                break;
            case SDLK_a:
                break;
            case SDLK_w:
                break;
            case SDLK_s:
                break;
            case SDLK_d:
                break;
            case SDLK_RALT:
                break;
            case SDLK_LALT:
                break;
            case SDLK_TAB:
                break;
            case SDLK_ESCAPE:
                return false;
                break;
            }
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
        case SDL_WINDOWEVENT:
            switch(event.window.event)
            {
            case SDL_WINDOWEVENT_EXPOSED:
                break;
            case SDL_WINDOWEVENT_MOVED:
                break;
            }
            break;
        case SDL_MOUSEWHEEL:
            break;

        }

    }
    const Uint8 * key_states =SDL_GetKeyboardState(nullptr);

    // if alt + tab was pressed
    if((key_states[SDL_SCANCODE_LALT]||key_states[SDL_SCANCODE_RALT])&&key_states[SDL_SCANCODE_TAB])
    {
        // minimize the window
        video::Video_subsystem::minimize();
    }
    return true;
}

/**
 * Group selection mode's game loop
 */

bool Group_selection_mode::run()
{
    // handle that input
    if(handle_input()==false)
    {
        return false;
    }

    main_gui.update();

    // reload video subsystem
    video::Video_subsystem::reload();
    // main logic here
    main_background->show();
    main_gui.show();
    video::Video_subsystem::update_screen();
    // check the fps and sleep the necessary time

    return true;
}

/**
 * Constructor
 */

Group_selection_mode::Group_selection_mode(utility::Configuration * init_config):
    main_config(init_config),
    groups(std::string("./config/")+main_config->find_string("group_config"))
{
    gui::Button * next_group;
    next_group = new gui::Button(100,100);
    next_group->init_image(main_config->find_string("left_arrow"));
    next_group->change_position(video::Video_subsystem::get_width()-next_group->get_width(),video::Video_subsystem::get_height()/2-next_group->get_height()/2);
    auto next_function = []()
    {

    };
    next_group->init_function(next_function);

    gui::Button * previous_group;
    previous_group = new gui::Button(100,100);
    previous_group->init_image(main_config->find_string("left_arrow"));
    previous_group->get_texture().set_angle(180);
    previous_group->change_position(0,video::Video_subsystem::get_height()/2-previous_group->get_height()/2);
    auto previous_function = []()
    {

    };
    previous_group->init_function(previous_function);

    main_gui.add_element(next_group);
    main_gui.add_element(previous_group);

    main_background = new gui::Background(main_config->find_string("main_background").c_str());
}

}// end of main_logic namespace
