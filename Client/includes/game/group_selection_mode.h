#ifndef GAMING_MODE_H_INCLUDED
#define GAMING_MODE_H_INCLUDED

#include "program_mode.h"
#include "../gui/background.h"


namespace game
{

class Group_selection_mode : public Program_mode
{
public :

    Group_selection_mode(utility::Configuration * init_config);
    bool run ()override;
    bool handle_input()override;

private:

    // background
    gui::Background * main_background;
    // event
    SDL_Event event;
    // configuration
    utility::Configuration * main_config;
};

}

#endif // GAMING_MODE_H_INCLUDED
