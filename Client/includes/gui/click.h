#ifndef CLICK_H_INCLUDED
#define CLICK_H_INCLUDED

#include <SDL.h>

namespace gui
{

/**
 * Class for click handling
 *
 */

class Click
{
    public:

    // determine if user clicked right now
    bool is_clicking();

    // determine if user has clicked that rectangle last frame and released the button
    bool has_clicked(SDL_Rect & location);

    //set last click's location
    void set_location(int x , int y);

    // set click last frame
    void set_clicked(bool was_clicked);

    private:

    //static to know last click location
    static SDL_Point last_click_location;

    static bool clicked_last_frame ;
};

}


#endif // CLICK_H_INCLUDED
