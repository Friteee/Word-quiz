#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "../video/texture.h"
#include "gui_element.h"

namespace gui{

class Button : public Gui_element
{
public:
    Button(int x , int y);
    void init_image(std::string image);
    void show()override;
    void update()override;
    void init_function(std::function<void()> init_on_click);
    void handle_click(int x, int y);
    ~Button();
private:
    // function, which is being called every time user clicks a button
    std::function<void()> on_click;
    // is the button clicked
    bool is_clicked = false;
    // button texture
    video::Texture button_texture;
};

}// end of gui namespace
#endif // BUTTON_H_INCLUDED
