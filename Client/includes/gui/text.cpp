

#include "text.h"
#include "../utility/functions.h"
#include "../video/window.h"
#include <cstdio>

namespace gui
{

Text::Text(utility::Configuration * config, std::string init_text, int x , int y, SDL_Color init_color_key)
{
    visible = true;
    text = init_text;

    color_key=init_color_key;
    color_key.a=255;

    font = TTF_OpenFont(config->find_string("font").c_str(),48);

    texture.init(text,color_key,font);

    location.x = x;
    location.y = y;
    location.w = texture.get_width();
    location.h = texture.get_height();
}

void Text::show()
{
    if(!visible)
    {
        return;
    }
    video::Video_subsystem::blit(texture.get_texture(),nullptr,&location);
}

void Text::update()
{

}

void Text::change_text(std::string init_text)
{
    text = init_text;
    texture.init(init_text,color_key,font);
    location.w = texture.get_width();
    location.h = texture.get_height();
}

}// end of namespace gui
