

#include "main_menu_mode.h"
#include "group_selection_mode.h"
#include "help_mode.h"
#include "gaming_mode.h"
#include "game_logic.h"
#include "../utility/stopwatch.h"
#include "../gui/click.h"
#include <cstdio>
#include <cmath>

namespace main_logic
{

/**
 * Running mode
 * Returns false if user wants to quit
 */

bool Main_menu_mode::run()
{

    if(handle_input()==false || quit == true)
    {
        return false;
    }
    video::Video_subsystem::reload();

    //update
    main_gui.update();


    //show
    background.show();
    main_gui.show();

    video::Video_subsystem::update_screen();

    return true;
}

/**
 * Input handling.
 * Used mostly to move the grid
 * Returns false if user wants to quit
 */

bool Main_menu_mode::handle_input()
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

Main_menu_mode::Main_menu_mode(utility::Configuration * init_config) :
    main_config(init_config),
    grid_speed(atoi(main_config->find_string("grid_speed").c_str())),
    grid_x(0),
    grid_y(0),
    change_mode(false),
    quit(false)
{
    music.init("sound/tetris.mp3");
    music.play();

    int button_x = video::Video_subsystem::get_width()/2 - 100;
    //add play button
    gui::Text_button * play_button = new gui::Text_button(main_config,"Play",button_x,100);
    auto play_click_function = [this]()
    {
        Game_logic::set_current_mode (new Gaming_mode (main_config) );
    };
    play_button->init_function(play_click_function);


    //add help button
    gui::Text_button * help_button = new gui::Text_button(main_config,"Help",button_x,200);
    auto help_click_function = [this]()
    {
        Game_logic::set_current_mode (new Help_mode (main_config) );
    };
    help_button->init_function(help_click_function);


    //add quit button
    gui::Text_button * quit_button = new gui::Text_button(main_config,"Quit",button_x,300);
    auto quit_click_function = [this]()
    {
        this->quit=true;
    };
    quit_button->init_function(quit_click_function);


    //add elements to gui manager
    main_gui.add_element(play_button);
    main_gui.add_element(help_button);
    main_gui.add_element(quit_button);

    // background
    background.change_image(main_config->find_string("main_background").c_str());

}

}//end of main_logic namespace

