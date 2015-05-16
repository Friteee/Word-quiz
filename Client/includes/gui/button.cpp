
#include "button.h"
#include "../video/window.h"
#include <cstdio>

namespace gui {

Button::Button(int x , int y)
{
    visible = true;

    location.x = x;
    location.y = y;

}

void Button::init_image(std::string image)
{
    texture.init(image , SDL_Color{255,0,255,255});
    location.w = texture.get_width();
    location.h = texture.get_height();
}

void Button::init_image(video::Texture init_texture)
{
    texture = init_texture;
    location.w = texture.get_width();
    location.h = texture.get_height();
}

video::Texture & Button::get_texture()
{
    return texture;
}

void Button::show()
{
    if(!visible)
    {
        return;
    }
    video::Video_subsystem::blit(texture.get_texture(), nullptr, &location , texture.get_angle() , nullptr , SDL_FLIP_NONE);
}

void Button::update()
{

}

void Button::init_function(std::function<void()> init_on_click)
{
    on_click = init_on_click;
}

void Button::handle_click(int x, int y)
{
    if(visible && x > location.x && x < location.x + location.w && y > location.y && y < location.y + location.h)
    {
        if(on_click)
            on_click();
        else
            printf("Warning : no function specified for a button\n");
    }
}

}
