// *** ADDED BY HEADER FIXUP ***
#include <cassert>
// *** END ***

#include "word_group.h"
#include "../utility/functions.h"
#include <cstdio>
#include <assert.h>
#include <algorithm>

namespace game
{

Word_group::Word_group(utility::Configuration cfg)
{
    std::vector <std::string> words_and_textures = cfg.find_strings("word");
    leaderboards_filename = cfg.find_string("leaderboards");
    name = cfg.find_string("name");

    for(auto a : words_and_textures)
    {
        std::vector<std::string> buffer;
        buffer = utility::get_separated_strings(a);
        if(buffer.size() != 2)
        {
            printf("Either word or its image is not written\n");
            assert(0);
        }
        words.push_back(buffer[0]);
        video::Texture texture_buffer;
        texture_buffer.init(std::string("./images/")+name+std::string("/")+buffer[1]);
        textures.push_back(texture_buffer);
    }

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

unsigned int Word_group::get_size()
{
    return words.size();
}

void Word_group::delete_word(unsigned int index)
{
    if(index > words.size())
    {
        printf("Wrong index provided for work group deletion\n");
        assert(1);
    }
    words.erase(words.begin()+index);
    textures.erase(textures.begin()+index);
}

std::string Word_group::get_leaderboards()
{
    return leaderboards_filename;
}

}
