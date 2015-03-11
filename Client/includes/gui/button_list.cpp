#include "button_list.h"

namespace gui
{

void Button_list::update()
{
    for(auto element : elements)
    {
        element->update();
    }
}

void Button_list::show()
{
    for(auto element : elements)
    {
        element->show();
    }
}





}//end of gui namespace
