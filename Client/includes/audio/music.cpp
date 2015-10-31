#include "music.h"
#include <cstdio>

namespace audio
{


void Music::init(std::string init_sound)
{

    Mix_Music * buffer = Mix_LoadMUS( init_sound.c_str());
    if( buffer == NULL )
    {
        printf( "Failed to load a sound effect from %s! SDL_mixer Error: %s\n", init_sound.c_str() , Mix_GetError() );
    }
    sound = std::make_shared<Mix_Music*>( buffer );
    Mix_VolumeMusic(volume);
}

void Music::play()
{
    Mix_PlayMusic( *sound.get(), -1 );
}

void Music::stop()
{
    Mix_HaltMusic();
}

void Music::pause()
{
    //If the music is paused
    if( Mix_PausedMusic() == 1 )
    {
        //Resume the music
        Mix_ResumeMusic();
    }
    //If the music is playing
    else
    {
        //Pause the music
        Mix_PauseMusic();
    }
}

Music::~Music()
{
    Mix_FreeMusic( *sound.get() );
}

void Music::change_volume(int amount)
{
    if(volume + amount> 128 && amount > 0)
        volume = 128;
    else if (volume + amount > 128 && amount < 0)
        volume = 0;
    else
        volume += amount;
    Mix_VolumeMusic(volume);
}

void Music::set_volume(unsigned int init_volume)
{
    volume = init_volume;
    Mix_VolumeMusic(volume);
}

unsigned int Music::volume = 24;

}
