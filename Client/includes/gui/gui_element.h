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
    inline int get_height()
    {
        return texture.get_height();
    }
    inline int get_width()
    {
        return texture.get_width();
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
