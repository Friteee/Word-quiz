

#include "click.h"

namespace gui
{

bool Click::clicked_last_frame = false;

SDL_Point Click::last_click_location=SDL_Point {0,0};

bool Click::has_clicked()
{
    return Click::clicked_last_frame;
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

void Click::get_location(int & x, int & y)
{
    x = Click::last_click_location.x;
    y = Click::last_click_location.y;
}

}// end of gui namespace
