
#include "group_selection_mode.h"
#include "game_logic.h"

namespace game
{

/**
 * Group_selection's input handler
 */

bool Group_selection_mode::handle_input()
{
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
                return false;
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
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:

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
    // reload video subsystem
    video::Video_subsystem::reload();
    // main logic here
    main_background->show();
    video::Video_subsystem::update_screen();
    // check the fps and sleep the necessary time

    return true;
}

/**
 * Constructor
 */

Group_selection_mode::Group_selection_mode(utility::Configuration * init_config):
    main_config(init_config)
{

    main_background = new gui::Background(main_config->find_string("main_background").c_str());


}

}
