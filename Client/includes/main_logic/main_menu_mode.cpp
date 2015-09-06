
#include <cstdio>
#include <cmath>
#include "main_menu_mode.h"
#include "group_selection_mode.h"
#include "help_mode.h"
#include "gaming_mode.h"
#include "game_logic.h"
#include "../gui/click.h"
#include "../gui/button.h "



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
            music.stop();
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
    music.init("sound/dendi.wav");
    music.play();

    int button_x = video::Video_subsystem::get_width()/2 - 100;
    //add play button
    gui::Text_button * play_button = new gui::Text_button(main_config,"Play",button_x,300);
    auto play_click_function = [this]()
    {
        Game_logic::set_current_mode (new Group_selection_mode (main_config) );
    };
    play_button->init_function(play_click_function);


    //add help button
    gui::Text_button * help_button = new gui::Text_button(main_config,"Help",button_x,400);
    auto help_click_function = [this]()
    {
        Game_logic::set_current_mode (new Help_mode (main_config) );
    };
    help_button->init_function(help_click_function);


    //add quit button
    gui::Text_button * quit_button = new gui::Text_button(main_config,"Quit",button_x,500);
    auto quit_click_function = [this]()
    {
        music.stop();
        this->quit=true;
    };
    quit_button->init_function(quit_click_function);

    gui::Button * decrease_volume;
    decrease_volume = new gui::Button(100,100);
    decrease_volume->init_image(main_config->find_string("decrease_volume"));
    decrease_volume->change_position(video::Video_subsystem::get_width() - 4.5 * decrease_volume->get_width() ,decrease_volume->get_height()/2);
    auto decrease_volume_function = []()
    {
        audio::Music::change_volume(-10);
    };
    decrease_volume->init_function(decrease_volume_function);

    gui::Button * increase_volume;
    increase_volume = new gui::Button(100,100);
    increase_volume->init_image(main_config->find_string("increase_volume"));
    increase_volume->change_position(video::Video_subsystem::get_width() - 1.5 * increase_volume->get_width() ,increase_volume->get_height()/2);
    auto increase_volume_function = []()
    {
        audio::Music::change_volume(10);
    };
    increase_volume->init_function(increase_volume_function);

    gui::Button * stop_music;
    stop_music = new gui::Button(100,100);
    stop_music->init_image(main_config->find_string("note"));
    stop_music->change_position(video::Video_subsystem::get_width() - 3 * stop_music->get_width() ,stop_music->get_height()/2);
    std::function<void()> stop_music_function = [stop_music,this]()
    {

    };
    stop_music->init_function(stop_music_function);


    //add elements to gui manager
    main_gui.add_element(play_button);
    main_gui.add_element(help_button);
    main_gui.add_element(quit_button);
    main_gui.add_element(decrease_volume);
    main_gui.add_element(increase_volume);
    main_gui.add_element(stop_music);

    // background
    background.change_image(main_config->find_string("main_background").c_str());

}

}//end of main_logic namespace

