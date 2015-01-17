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
 * Modes of editor modes
 */
enum Modes_of_editor
{
    tile_picker, map_editing
};

/**
 * Editor mode for main game logic
 */

class Editor_mode : Program_mode
{
    public :

    Editor_mode(utility::Configuration * init_config);
    bool       run ()override;
    bool       handle_input()override;

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
    // mode of editor mode
    // "We know that you like modes, so we've put a mode in your mode"
    Modes_of_editor          mode;
    gui::Background          background;
    bool                     change_mode;
};

} // end of game namespace

#endif // EDITOR_MODE_H_INCLUDED
