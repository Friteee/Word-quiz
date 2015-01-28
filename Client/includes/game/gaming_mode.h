#ifndef GAMING_MODE_H_INCLUDED
#define GAMING_MODE_H_INCLUDED

#include "program_mode.h"
#include "../gui/background.h"


namespace game
{

class Gaming_mode : public Program_mode
{
    public :

    Gaming_mode(utility::Configuration * init_config);
    bool run ()override;
    bool handle_input()override;
    void stop()override;

    private:

    // background
    gui::Background * main_background;
    // event
    SDL_Event event;
    // configuration
    utility::Configuration * main_config;
    // does user wants to change programs mode?
    bool change_mode;
};

}

#endif // GAMING_MODE_H_INCLUDED
