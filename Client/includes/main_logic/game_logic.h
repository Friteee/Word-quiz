#ifndef GAME_LOGIC_H_INCLUDED
#define GAME_LOGIC_H_INCLUDED

#include "../video/window.h"
#include "../gui/background.h"
#include "../video/camera.h"
#include "../utility/configuration.h"
#include "../audio/audio.h"
#include "gaming_mode.h"
#include "main_menu_mode.h"

namespace main_logic
{


/**
 * Game_logic class
 * First thing to be created
 */

class Game_logic
{

public:

    // initialization of game_logic
    static bool initialize(const char *);
    // main loop
    static void run();
    // getter of instance of game_logic
    static Game_logic& get_instance();
    // set the current mode
    static void set_current_mode(Program_mode * init_mode);
    ~Game_logic();

private:
    // configuration
    utility::Configuration main_config;
    //width and height
    int                    width,
                           height;
    //is it full-screen?
    bool                   fullscreen;
    // constructor
    Game_logic();
    // remove all other means to create video_subsystem
    Game_logic( Game_logic const& x)= delete;
    // instance for maintaining singleton
    static Game_logic* instance;
    // bool to know if the instance was created without errors
    bool           is_created;
    // event handler
    SDL_Event      event;
    // bool to quit out of main loop
    bool           quit_program;
    // current mode
    Program_mode * current;
    // program mode marked for deletion
    Program_mode * previous;

};





}// game logic namespace

#endif // GAME_LOGIC_H_INCLUDED
