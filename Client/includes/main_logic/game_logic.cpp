
#include <SDL.h>
#include <stdio.h>
#include "game_logic.h"
#include "../video/window.h"
#include "../video/camera.h"
#include "../utility/stopwatch.h"
#include "../utility/functions.h"
#include "../utility/configuration.h"
#include <cstdlib>

namespace main_logic
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
    quit_program (false)
{
    video::Video_subsystem::set_programs_name(main_config.find_string("programs_name").c_str());

    current = new Main_menu_mode (&main_config);
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
    unsigned int fps_cap = atoi(instance->main_config.find_string("fps_cap").c_str());
    bool fps_cap_enabled = instance->main_config.find_string("fps_cap_enabled").c_str()==string("true");

    // timers to enable sleeping and count of fps
    utility::Stopwatch sleep_timer;
    utility::Stopwatch fps_timer;
    fps_timer.start();
    sleep_timer.start();
    // integer for fps, overflow is unlikely :)
    unsigned int fps=0;

    while(instance->current->run())
    {
        fps++;
        if(fps_timer.get_ticks()>1000)
        {
            printf("Current fps = %u \n",fps);
            fps_timer.reload();
            fps=0;
        }
        if(sleep_timer.get_ticks()<1000/fps_cap&&fps_cap_enabled)
        {
            SDL_Delay(1000/fps_cap-sleep_timer.get_ticks());
        }
        sleep_timer.reload();
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

void Game_logic::set_current_mode(Program_mode * init_mode)
{
    // delete previous instance
    delete instance->previous;
    // current program mode instance is now previous instance
    instance->previous = instance->current;
    // current instance is now user's assigned
    instance->current = init_mode;
}

}// end of namespace main_logic

