

#include "text.h"
#include "../utility/functions.h"
#include "../video/window.h"
#include <cstdio>

namespace gui
{

Text::Text(utility::Configuration * config, std::string init_text, int x , int y, int init_text_size, SDL_Color init_color_key)
{
    visible = true;
    text = init_text;
    text_size = init_text_size;

    color_key=init_color_key;
    color_key.a=255;

    font = TTF_OpenFont(config->find_string("font").c_str(),text_size);

    if(!text.empty())
    {
        texture.init(text,color_key,font);

        location.w = texture.get_width();
        location.h = texture.get_height();
    }
    else
    {
        location.w = 0;
        location.h = 0;
    }
    location.x = x;
    location.y = y;
}

void Text::show()
{
    if(!visible||text.length()==0)
    {
        return;
    }
    video::Video_subsystem::blit(texture.get_texture(),nullptr,&location);
}

void Text::update()
{

}

Text::~Text()
{
    TTF_CloseFont(font);
}

void Text::change_text(std::string init_text)
{
    text = init_text;
    if(text.length()!=0)
    {
        texture.init(init_text,color_key,font);
        location.w = texture.get_width();
        location.h = texture.get_height();
    }
}

void Text::handle_click(int x, int y)
{

}

unsigned int Text::get_length()
{
    return text.length();
}

}// end of namespace gui
