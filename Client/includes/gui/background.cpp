#include <stdio.h>
#include <SDL.h>
#include "../video/window.h"
#include <string>
#include <memory>
#include "background.h"

namespace gui{


/**
 * Default background constructor
 */
Background::Background()
{
    location.x=0;
    location.y=0;
    location.w=0;
    location.h=0;
}

/**
 * Constructor for background
 * use c style location string
 */
Background::Background(const char* image_location)
{
    texture.init(image_location);
    location.x=0;
    location.y=0;
    location.w=texture.get_width();
    location.h=texture.get_height();
}

/**
 * Constructor for background
 * overloaded to use shared_ptr
 */
Background::Background(shared_ptr<SDL_Surface*>copied_surface)
{
    texture.init(*copied_surface);
    location.x=0;
    location.y=0;
    location.w=texture.get_width();
    location.h=texture.get_height();
}

/**
 * Copy constructor
 */
Background::Background(const Background &copied_object)
{
    texture=copied_object.texture;
    location=copied_object.location;
}

/**
 * Copy assignment operator
 */
Background& Background::operator=(const Background &copied_object)
{
    if(this!=&copied_object)
    {
        this->texture=copied_object.texture;
        this->location=copied_object.location;
    }
    return *this;
}

/**
 * Move constructor
 */
Background::Background(Background && moved_object)
{
    texture=moved_object.texture;
    location=moved_object.location;
}

/**
 * Move assignment operator
 */
Background & Background::operator=(Background && moved_object)
{
    texture=moved_object.texture;
    location=moved_object.location;
    return *this;
}

/**
 * Destructor
 * Frees the memory for shared pointers
 */
Background::~Background()
{

}

/**
 * Show method
 * Use it to blit background to screen
 */
void Background::show()
{
    video::Video_subsystem::blit(texture.get_texture() , &location , NULL);
}

/**
 * Method to change image
 * Uses image location string (as for constructor)
 */
void Background::change_image(const char * image_location)
{
    texture.init(image_location);
    location.w = texture.get_width();
    location.h = texture.get_height();
}

/**
 * Method to change image
 * Uses shared pointer (as in overloaded constructor)
 */
void Background::change_image(shared_ptr<SDL_Surface*>copied_surface)
{
    texture.init(*copied_surface);
    location.w = texture.get_width();
    location.h = texture.get_height();
}


}// end of objects namespace
