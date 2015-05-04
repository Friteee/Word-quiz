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
private:
    std::shared_ptr<Mix_Chunk *> sound;

};

}
