#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <SDl_mixer.h>
#include <string>
#include <memory>

namespace audio
{

class Music
{

public:
    void init(std::string init_sound);
    void play();
    void stop();
    void pause();
    ~Music();
    static void change_volume(unsigned int volume);
private:
    std::shared_ptr<Mix_Music *> sound;

};

}

#endif // MUSIC_H_INCLUDED
