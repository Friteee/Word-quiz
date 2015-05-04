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
private:
    std::shared_ptr<Mix_Music *> sound;

};

}
