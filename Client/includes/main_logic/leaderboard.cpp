
#include "leaderboard.h"

namespace main_logic
{

Leaderboard::Leaderboard(std::string filename , utility::Configuration * config)
{
    scores.init(filename);
    scores.save();
    main_background.change_image(config->find_string("main_background").c_str() );

}

bool Leaderboard::run()
{
    if(handle_input()==false)
    {
        return false;
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

bool Leaderboard::handle_input()
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
                return false;
                break;
            case SDLK_q:
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

}// end of main logic namespace
