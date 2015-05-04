
#include <SDL_mixer.h>
#include <cstdio>
#include "audio.h"

namespace audio {

Audio_subsystem* Audio_subsystem::instance = nullptr;

bool Audio_subsystem::initialize_subsystem()
{
    Audio_subsystem::instance = new Audio_subsystem();
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }
    return true;
}

Audio_subsystem::Audio_subsystem()
{

}

}
