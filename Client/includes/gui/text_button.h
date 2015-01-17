#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "gui_element.h"
#include <functional>
#include "../utility/configuration.h"

namespace gui
{

class Text_button : public Gui_element
{
    public:

    Text_button(utility::Configuration * config, std::string init_text , int x , int y);
    void show()override;
    void update()override;
    void init_function(std::function<void()> init_on_click);
    void change_text(std::string init_text);
    ~Text_button();

    private:

    // function, which is being called every time user clicks a button
    std::function<void()> on_click;
    // boolean to know if the button is being clicked
    bool                  is_clicked;
    // text to be blended
    std::string text;
    // font
    TTF_Font * font;
    // text color
    SDL_Color color;


};

}// end of object namespace

#endif // BUTTON_H_INCLUDED
