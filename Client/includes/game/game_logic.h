#ifndef GAME_LOGIC_H_INCLUDED
#define GAME_LOGIC_H_INCLUDED

#include "../video/window.h"
#include "../gui/background.h"
#include "../video/camera.h"
#include "../utility/configuration.h"
#include "gaming_mode.h"
#include "main_menu_mode.h"

namespace game{


/**
 * Game_logic class
 * First thing to be created
 */

class Game_logic{

    public:

    // initialization of game_logic
    static bool initialize(const char *);
    // main loop
    static void run();
    // getter of instance of game_logic
    static Game_logic& get_instance();
    ~Game_logic();

    private:
    // configuration
    utility::Configuration main_config;
    int width,
        height;
    bool fullscreen;
    // constructor
    Game_logic();
    // remove all other means to create video_subsystem
    Game_logic( Game_logic const& x)= delete;
    // instance for maintaining singleton
    static Game_logic* instance;
    // bool to know if the instance was created without errors
    bool is_created;
    // flag for signaling, if the game should run an editor
    bool is_editor;
    // event handler
    SDL_Event event;
    // bool to quit out of main loop
    bool quit_program;
    // tile map
    Editor_mode editor;
    // mode for gaming
    Gaming_mode gaming_mode;

};





}// game logic namespace

#endif // GAME_LOGIC_H_INCLUDED
