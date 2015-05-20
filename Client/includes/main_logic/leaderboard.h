#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

#include <string>
#include "program_mode.h"
#include "../gui/background.h"
#include "../gui/gui_manager.h"
#include "../gui/click.h"
#include "../game/highscore.h"

namespace main_logic
{

class Leaderboard : public Program_mode
{
public :

    Leaderboard(std::string filename , utility::Configuration * init_config );
    bool run ()override;
    bool handle_input()override;

private:
    // background
    gui::Background          main_background;
    // event
    SDL_Event                event;
    // gui elements manager
    gui::Gui_manager         main_gui;
    //config
    utility::Configuration * config;
    // highscores
    game::Highscore          scores;


};

}


#endif // LEADERBOARD_H_INCLUDED
