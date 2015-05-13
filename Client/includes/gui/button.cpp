
#include "button.h"

namespace gui {

Button::Button(int x , int y)
{
    visible = true;


    location.x = x;
    location.y = y;

    is_clicked = false;
}

void Button::init_image(std::string image)
{

}

void Button::show()
{
    if(!visible)
    {
        return;
    }
    video::Video_subsystem::blit(texture.get_texture(),nullptr,&location);
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

}

Button::~Button()
{

}

}
