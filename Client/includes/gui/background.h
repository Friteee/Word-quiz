#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <stdio.h>
#include <SDL.h>
#include "../video/window.h"
#include "../video/texture.h"
#include <string>
#include <memory>
#include <deque>

using namespace std;

namespace gui
{

/**
 * Background class
 * Probably will use it only once
 * Multiple background usage is available
 * Use background_pool for declaring
 */

class Background
{

public:
    //default constructor
    Background();
    // background constructor if we have image location
    Background(const char* image_location );
    // background constructor if we have another surface
    Background(shared_ptr<SDL_Surface*>copied_surface);
    // copy constructor
    Background(const Background &copied_object) ;
    //copy assignment operator
    Background& operator=(const Background &copied_object) ;
    // move constructor
    Background(Background && moved_object);
    // move assignment
    Background& operator=(Background && copied_object) ;
    // destructor - frees shared pointers
    ~Background();
    // method to show background
    void show() ;
    // method to change the image of background
    void change_image(const char * image_location);
    // method to change image from surface
    void change_image(shared_ptr<SDL_Surface*>copied_surface);

private:

    video::Texture texture;
    // rectangle to hold location of background
    SDL_Rect location;

};


}// end of objects namespace

#endif // BACKGROUND_H_INCLUDED
