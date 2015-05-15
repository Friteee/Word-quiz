#ifndef GUI_ELEMENT_H_INCLUDED
#define GUI_ELEMENT_H_INCLUDED

#include <SDL.h>
#include "../video/texture.h"

namespace gui
{

/**
 * Gui element base class
 * Almost the same thing as object, but no collision with this one
 * And objects are used only with camera, while gui elements are drawn straight to screen
 */

class Gui_element
{
public:

    virtual void show() = 0;
    virtual void update() = 0;
    virtual void handle_click(int x, int y)= 0 ;

    //inline functions

    inline void hide()
    {
        visible=false;
    }
    inline void unhide()
    {
        visible=true;
    }
    inline bool get_visibility()
    {
        return visible;
    }
    inline void set_for_deletion()
    {
        marked_for_deletion=true;
    }
    inline bool is_deleted()
    {
        return marked_for_deletion;
    }
    inline void change_position(int x, int y)
    {
        location.x=x;
        location.y=y;
    }
    inline int get_width()
    {
        return location.w;
    }
    inline int get_height()
    {
        return location.h;
    }
    inline void set_width(int width)
    {
        location.w = width;
    }
    inline void set_height(int height)
    {
        location.h = height;
    }
    virtual ~Gui_element() {}

protected :

    SDL_Rect       location;
    video::Texture texture;
    bool           visible,
                   marked_for_deletion = false;

};

}//end of object namespace

#endif // GUI_ELEMENT_H_INCLUDED
