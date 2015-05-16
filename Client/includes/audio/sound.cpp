#include "sound.h"
#include <cstdio>

namespace audio
{


void Sound::init(std::string init_sound)
{
    Mix_Chunk * buffer = Mix_LoadWAV( init_sound.c_str());
    if( buffer == NULL )
    {
        printf( "Failed to load a sound effect from %s! SDL_mixer Error: %s\n", init_sound.c_str() , Mix_GetError() );
    }
    sound = std::make_shared<Mix_Chunk*>( buffer );
}

void Sound::play()
{
    Mix_PlayChannel( 1, *sound.get(), 0 );
}

Sound::~Sound()
{
    Mix_FreeChunk( *sound.get() );
}

void Sound::change_volume(int amount)
{

    if(volume + amount> 128 && amount > 0)
        volume = 128;
    else if (volume + amount > 128 && amount < 0)
        volume = 0;
    else
        volume += amount;

    Mix_Volume(1,volume);
}

void Sound::set_volume(unsigned int init_volume)
{
    volume = init_volume;
    Mix_Volume(1,volume);
}

unsigned int Sound::volume = 128;

}
