
#include "help_mode.h"
#include "../video/window.h"
#include <cstdio>

namespace game
{

Help_mode::Help_mode(utility::Configuration * config):
    main_config(config),
    change_mode(false)
{
    fps_timer.start();
}

bool Help_mode::run()
{
    while(1)
    {
        fps++;
        if(handle_input()==false)
        {
            return false;
        }
        else if(change_mode==true)
        {
            return true;
        }
        video::Video_subsystem::reload();

        //update
        main_gui.update();

        main_gui.show();

        video::Video_subsystem::update_screen();

        if(fps_timer.get_ticks()>1000)
        {
            printf("Current ticks = %i\n",fps);
            fps=0;
            fps_timer.reload();
        }
    }
    return true;
}

void Help_mode::stop()
{

}

bool Help_mode::handle_input()
{
    return true;
}

}//end of game namespace
