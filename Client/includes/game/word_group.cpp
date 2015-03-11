
#include "word_group.h"
#include "../utility/functions.h"
#include <cstdio>
#include <assert.h>

namespace game
{

Word_group::Word_group(utility::Configuration * cfg)
{
    std::vector <std::string> words_and_textures = cfg->find_strings("word");
    for(auto a : words_and_textures)
    {
        std::vector<std::string> buffer;
        buffer = utility::get_separated_strings(a);
        words.push_back(buffer[0]);
        video::Texture texture_buffer;
        texture_buffer.init(buffer[1]);
        textures.push_back(texture_buffer);
    }
    name = cfg->find_string("name");
}

std::string Word_group::get_name()
{
    return name;
}

std::string Word_group::get_word   (unsigned int index)
{
    if(index > words.size())
    {
        printf("Index passed to word group is too big");
        assert(1);
    }
    return words[index];
}

video::Texture & Word_group::get_texture(unsigned int index)
{
    if(index > textures.size())
    {
        printf("Index passed to word group is too big");
        assert(1);
    }
    return textures[index];
}

}
