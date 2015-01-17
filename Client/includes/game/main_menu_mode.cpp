

#include "main_menu_mode.h"
#include "../utility/timer.h"
#include "../gui/click.h"
#include <cstdio>
#include <cmath>

namespace game
{

/**
 * Running mode
 * Returns false if user wants to quit
 */

bool Editor_mode::run()
{
    fps_timer.start();
    int fps = 0;
    while(1)
    {
        fps++;
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
        background.show();
        main_gui.show();

        video::Video_subsystem::update_screen();


        if(fps_timer.get_ticks()>1000)
        {
            printf("Current ticks = %i\n",fps);
            fps=0;
            fps_timer.reload();
        }
    }

}

/**
 * Input handling.
 * Used mostly to move the grid
 * Returns false if user wants to quit
 */

bool Editor_mode::handle_input()
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
                break;
            case SDLK_q:
                return false;
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

/**
 * Editor constructor
 */

Editor_mode::Editor_mode(utility::Configuration * init_config) :
    main_config(init_config),
    grid_speed(atoi(main_config->find_string("grid_speed").c_str())),
    grid_x(0),
    grid_y(0),
    mode(map_editing),
    change_mode(false)
{
    //create pointers and objects for gui elements
    gui::Text_button * play_button = new gui::Text_button(main_config,"Play",550,100);

    auto play_click_function = [this]()
    {
        this->change_mode=true;
    };



    play_button->init_function(play_click_function);

    //add elements to gui manager
    main_gui.add_element(play_button);

    // background
    background.change_image(main_config->find_string("main_background").c_str());

}

}//end of game namespace

