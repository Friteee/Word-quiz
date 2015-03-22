#ifndef GAMING_MODE_H_INCLUDED
#define GAMING_MODE_H_INCLUDED

#include "program_mode.h"
#include "../gui/background.h"
#include "../gui/gui_manager.h"
#include "../game/word_group.h"
#include "../video/texture.h"
#include <string>

namespace main_logic
{

class Gaming_mode : public Program_mode
{
public :

    Gaming_mode(utility::Configuration * init_config);
    bool run ()override;
    bool handle_input()override;

private:

    // background
    gui::Background        * main_background;
    // event
    SDL_Event                event;
    // configuration
    utility::Configuration * main_config;
    // word group
    game::Word_group         main_group;
    // word we are trying to guess
    std::string              word;
    // texture of the word
    video::Texture           word_image;
    // gui elements manager
    gui::Gui_manager         gui_manager;

};

}

#endif // GAMING_MODE_H_INCLUDED
