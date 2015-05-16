#ifndef BUTTONX_H_INCLUDED
#define BUTTONX_H_INCLUDED

#include "../video/texture.h"
#include "gui_element.h"

namespace gui
{

class Button : public Gui_element
{
public:
    Button(int x , int y);
    void             init_image(std::string image);
    void             init_image(video::Texture init_texture);
    void             show()override;
    void             update()override;
    void             init_function(std::function<void()> init_on_click);
    void             handle_click(int x, int y)override;
    video::Texture & get_texture();
private:
    // function, which is being called every time user clicks a button
    std::function<void()> on_click;
    // is the button clicked
    bool is_clicked = false;
};

} // end of gui namespace

#endif // BUTTONX_H_INCLUDED
