#include <SDL.h>
#include "video/window.h"
#include "game/game_logic.h"
#include <stdio.h>

using namespace std;

int main(int argc, char* args[])
try{
    bool error_check;
    if(argc==2)
    {
        error_check = game::Game_logic::initialize(args[1]);
    }
    else
    {
        error_check = game::Game_logic::initialize(nullptr);
    }
    if(error_check==false)
    {
        printf("Couldn't initialize the game\n");
    }
    else
    {
        printf("Game is initialized\n");
    }
    game::Game_logic::run();
    return 0;
}
catch (exception e)
{
    printf("\nerror = %s \n",e.what());
    return 1;
}
