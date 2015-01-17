
#include <SDL.h>
#include <stdio.h>
#include "game_logic.h"
#include "../video/window.h"
#include "../video/camera.h"
#include "../utility/timer.h"
#include "../utility/functions.h"
#include "../utility/configuration.h"
#include <cstdlib>

namespace game
{

// defines for width , height AND FPS
// used as (and only as) default values
#define WIDTH 800
#define HEIGHT 600
#define FPS 1000
#define FPS_CAP false

Game_logic *Game_logic::instance = nullptr;

/**
 * Function to get game_logic
 * returns instance or null if not created
 */
Game_logic& Game_logic::get_instance()
{
    return *Game_logic::instance;
}

/**
 * function to initialize subsystem
 * returns true on success or if the system was already initialized, false on failure
 */
bool Game_logic::initialize(const char* filename)
{

    if(instance!=nullptr)
    {
        return true;
    }
    // enable SDL system
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS))
    {
        printf("Couldn't initialize SDL subsystems\n");
        printf("Error = %s\n", SDL_GetError());
    }
    if(TTF_Init())
    {
        printf("Couldn't initialize SDL true type font library\n");
        printf("Error = %s\n", TTF_GetError());
    }
    instance = new Game_logic ;
    return instance->is_created ;
}

/**
 * subsystems constructor
 */
Game_logic::Game_logic():
    main_config  ("./config/main_config.cfg") ,
    width        (atoi(main_config.find_string("width").c_str())!=0?atoi(main_config.find_string("width").c_str()):WIDTH),
    height       (atoi(main_config.find_string("height").c_str())!=0?atoi(main_config.find_string("height").c_str()):HEIGHT),
    fullscreen   (main_config.find_string("fullscreen") == string("true") ),
    is_created   (video::Video_subsystem::initialize_subsystem(width , height , fullscreen)),
    is_editor    (main_config.find_string("editor")==string("true")),
    quit_program (false),
    editor       (&main_config),
    gaming_mode  (&main_config)
{
    video::Video_subsystem::set_programs_name(main_config.find_string("programs_name").c_str());

    // if we have full screen resize camera appropriately
    if(fullscreen)
    {
        SDL_Rect location;
        location.x=0;
        location.y=0;
        SDL_GetWindowSize(video::Video_subsystem::get_instance().get_window(),&location.w,&location.h);
    }
}

/**
 * Main programs loop
 */

void Game_logic::run()
{
    if(instance->is_editor&&instance->editor.run()==false)
        return;
    while(1)
    {
        if(!instance->is_editor&&instance->gaming_mode.run()==false)
            break;
        else if(!instance->is_editor)
            instance->is_editor=true;
        else if(instance->is_editor&&instance->editor.run()==false)
            break;
        else
            instance->is_editor=false;
    }
}


/**
 * function to call after the user presses that quit button
 */

Game_logic::~Game_logic()
{
    // quit the program
    SDL_QuitSubSystem(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS);
    SDL_Quit();
    return;
}



}// end of namespace game

