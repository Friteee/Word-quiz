#ifndef GROUP_SELECTION_MODE_H_INCLUDED
#define GROUP_SELECTION_MODE_H_INCLUDED

#include "program_mode.h"
#include "../gui/background.h"
#include "../gui/gui_manager.h"


namespace main_logic
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
    // config for groups
    utility::Configuration groups;
    // gui manager
    gui::Gui_manager main_gui;
    //group names
    std::vector<std::string> group_names;
    //group images
    std::vector<video::Texture> group_images;
    // current pos
    unsigned int position;
};

}

#endif // GAMING_MODE_H_INCLUDED
