#ifndef MAIN_MENU_MODE_H_INCLUDED
#define MAIN_MENU_MODE_H_INCLUDED

#include "program_mode.h"
#include "../gui/text_button.h"
#include "../gui/gui_manager.h"
#include "../gui/background.h"
#include "../utility/timer.h"
#include "../video/window.h"


namespace game
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
    void       stop()override;

    private:

    // main configuration
    utility::Configuration * main_config;
    // event
    SDL_Event                event;
    // timers to handle fps and grid movement
    utility::Timer           fps_timer;
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
};

} // end of game namespace

#endif // EDITOR_MODE_H_INCLUDED
