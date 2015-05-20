// *** ADDED BY HEADER FIXUP ***
#include <cassert>
// *** END ***

#include "progress_bar.h"
#include "../video/window.h"
#include<cstdio>
#include<assert.h>

namespace gui
{

void Progress_bar::handle_click(int x, int y)
{
    //do nothing
}

void Progress_bar::show()
{
    video::Video_subsystem::blit(texture.get_texture() , nullptr, &location);
    unsigned int red = current_ticks.get_ticks() * 255 / overall_ticks;
    unsigned int green = 255 - red;
    video::Video_subsystem::fill_rect(bar_location,red,green,0);
}

void Progress_bar::update()
{
    if(current_ticks.get_ticks() >= overall_ticks)
    {
        if(timer_function)
        {
            timer_function();
        }
        else
        {
            printf("No function is given for progress bar\n");
            assert(0);
        }
        current_ticks.reload();
    }
    bar_location.w = current_ticks.get_ticks() * (location.w-4) / overall_ticks;
}

void Progress_bar::set_function(std::function<void()> init_function)
{
    timer_function = init_function;
}

void Progress_bar::start()
{
    current_ticks.start();
}

void Progress_bar::reset()
{
    current_ticks.reload();
}

Progress_bar::Progress_bar(unsigned int init_overall , SDL_Rect init_location)
{
    overall_ticks = init_overall;
    location = init_location;
    // initializing surface for texture
    SDL_Surface * init_texture = SDL_CreateRGBSurface(0,location.w,location.h,32,0,0,0,0);
    // Filling the surface with white color.
    SDL_FillRect(init_texture, NULL, SDL_MapRGB(init_texture->format, 255, 255 , 255));
    bar_location.x = 2 ;
    bar_location.y = 2 ;
    bar_location.w = location.w - 4;
    bar_location.h = location.h - 4;
    // Filling the surface with black
    SDL_FillRect(init_texture, &bar_location, SDL_MapRGB(init_texture->format, 0, 0, 0));
    // Setting black as color key
    Uint32 key = SDL_MapRGB(init_texture->format,0,0,0);
    SDL_SetColorKey( init_texture , SDL_TRUE , key );
    texture.init( init_texture );

    bar_location.x = 2 + location.x;
    bar_location.y = 2 + location.y;

}

Progress_bar::~Progress_bar()
{

}

}//end of gui namespace
