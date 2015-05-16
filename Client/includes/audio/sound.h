#include <SDl_mixer.h>
#include <string>
#include <memory>

namespace audio
{

class Sound
{

public:
    void init(std::string init_sound);
    void play();
    ~Sound();
    static void set_volume(unsigned int volume);
    static void change_volume(int amount);
private:
    std::shared_ptr<Mix_Chunk *> sound;
    static unsigned int volume;

};

}
