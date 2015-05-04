
namespace audio
{

class Audio_subsystem
{

public:

    // function to initialize audio_subsystem
    static bool initialize_subsystem();

private:

    // constructor
    Audio_subsystem() ;
    // remove all other means to create audio_subsystem
    Audio_subsystem( Audio_subsystem const& x) = delete;
    Audio_subsystem &operator=( Audio_subsystem const& x) = delete;
    Audio_subsystem( Audio_subsystem && x) = delete;
    Audio_subsystem &operator=( Audio_subsystem && x) = delete;
    // instance of audio_subsystem
    static Audio_subsystem* instance;
};

}
