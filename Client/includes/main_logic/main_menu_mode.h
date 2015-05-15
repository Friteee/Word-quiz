#ifndef MAIN_MENU_MODE_H_INCLUDED
#define MAIN_MENU_MODE_H_INCLUDED

#include "program_mode.h"
#include "../gui/text_button.h"
#include "../gui/gui_manager.h"
#include "../gui/background.h"
#include "../gui/button.h"
#include "../utility/stopwatch.h"
#include "../video/window.h"
#include "../audio/music.h"



namespace main_logic
{

/**
 * Editor mode for main game logic
 */

class Main_menu_mode : public Program_mode
{
public :

    Main_menu_mode(utility::Configuration * init_config);
    bool       run ()override;
    bool       handle_input()override;

private:

    // main configuration
    utility::Configuration * main_config;
    // event
    SDL_Event                event;
    // timers to handle fps and grid movement
    utility::Stopwatch       fps_stopwatch;
    // gui manager
    gui::Gui_manager         main_gui;
    // speed of the grid
    int                      grid_speed;
    // buffers for speed movement
    double                   grid_x,
                             grid_y;
    //background
    gui::Background          background;
    bool                     change_mode;
    bool                     quit;
    //music
    audio::Music             music;
};

} // end of main_logic namespace

#endif // EDITOR_MODE_H_INCLUDED
