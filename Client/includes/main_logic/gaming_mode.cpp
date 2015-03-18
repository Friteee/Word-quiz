
#include "gaming_mode.h"
#include "game_logic.h"
#include <cstdlib>

namespace main_logic
{

/**
 * Gaming mode's input handler
 */

bool Gaming_mode::handle_input()
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
            {
                if(main_group.get_size() == 0)
                    continue;
                int index = rand() % main_group.get_size();
                word = main_group.get_word(index);
                word_image = main_group.get_texture(index);
                main_group.delete_word(index);
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
 * Gaming mode's game loop
 */

bool Gaming_mode::run()
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

    SDL_Rect blit_location ;

    blit_location.w = video::Video_subsystem::get_width()/4;
    blit_location.h = video::Video_subsystem::get_width()/4;
    blit_location.x = video::Video_subsystem::get_width()/2 - video::Video_subsystem::get_width()/8;
    blit_location.y = video::Video_subsystem::get_height()/2 - 300;

    video::Video_subsystem::blit(word_image.get_texture() , nullptr , &blit_location);

    video::Video_subsystem::update_screen();

    return true;
}

/**
 * Constructor
 */

Gaming_mode::Gaming_mode(utility::Configuration * init_config):
    main_config(init_config),
    main_group( utility::Configuration("config/groups/banana.cfg"))
{
    change_mode = false;
    main_background = new gui::Background(main_config->find_string("main_background").c_str());
    srand(SDL_GetTicks());

    int index = rand() % main_group.get_size();
    word = main_group.get_word(index);
    word_image = main_group.get_texture(index);
    main_group.delete_word(index);

}



}//end of main_logic namespace
