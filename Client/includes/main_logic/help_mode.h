#ifndef HELP_MODE_H_INCLUDED
#define HELP_MODE_H_INCLUDED

#include "program_mode.h"
#include "../utility/configuration.h"
#include "../utility/timer.h"
#include "../gui/gui_manager.h"
#include "../gui/background.h"

namespace main_logic
{

class Help_mode : public Program_mode
{
public:
    Help_mode(utility::Configuration * config);
    bool run()override;
    bool handle_input()override;
private:
    gui::Gui_manager         main_gui;
    utility::Configuration * main_config;
    bool                     change_mode;
    SDL_Event                event;
    gui::Background          main_background;
};

}//end of main_logic namespace

#endif // HELP_MODE_H_INCLUDED
