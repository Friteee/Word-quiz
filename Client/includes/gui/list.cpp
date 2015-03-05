#include "list.h"

namespace gui
{

template <typename Element> void List<Element>::update()
{
    for(auto element : elements)
    {
        element->update();
    }
}

template <typename Element> void List<Element>::show()
{
    for(auto element : elements)
    {
        element->show();
    }
}



}//end of gui namespace
