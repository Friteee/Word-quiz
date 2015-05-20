
#include "../utility/configuration.h"
#include "../video/texture.h"
#include <string>
#include <vector>

namespace game
{

class Word_group
{

public:
    Word_group(utility::Configuration words_config);
    std::string      get_name();
    std::string      get_word   (unsigned int index);
    video::Texture & get_texture(unsigned int index);
    unsigned int     get_size();
    std::string      get_leaderboards();
    void             delete_word(unsigned int index);

private:
    std::string name;
    std::string leaderboards_filename;
    std::vector <video::Texture> textures;
    std::vector <std::string> words;
};

}
