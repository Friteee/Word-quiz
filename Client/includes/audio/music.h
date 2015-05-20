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
    static void stop();
    void pause();
    ~Music();
    static void set_volume(unsigned int volume);
    static void change_volume(int amount);
private:
    std::shared_ptr<Mix_Music *> sound;
    static unsigned int volume ;

};

}

#endif // MUSIC_H_INCLUDED
