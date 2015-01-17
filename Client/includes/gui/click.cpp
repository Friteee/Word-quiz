


#include "click.h"

namespace gui
{

bool Click::clicked_last_frame = false;

SDL_Point Click::last_click_location=SDL_Point{0,0};


bool Click::has_clicked(SDL_Rect & location)
{
    if(!Click::clicked_last_frame)
    {
        return false;
    }
    else if(Click::last_click_location.x>location.x&&Click::last_click_location.x<location.x+location.w&&
            Click::last_click_location.y>location.y&&Click::last_click_location.y<location.y+location.h)
    {
        return true;
    }
    else
        return false;
}

bool Click::is_clicking()
{
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT);
}

void Click::set_clicked(bool was_clicked)
{
    Click::clicked_last_frame = was_clicked;
}

void Click::set_location(int x, int y)
{
    Click::last_click_location.x = x;
    Click::last_click_location.y = y;
}

}// end of gui namespace
