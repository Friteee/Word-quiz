

#include "gui_manager.h"

namespace gui
{

Gui_manager::Gui_manager()
{

}

Gui_manager::~Gui_manager()
{
    for(auto & a : elements)
    {
        delete a;
    }
}

void Gui_manager::add_element(Gui_element * added_element)
{
    elements.push_back(added_element);
}

void Gui_manager::update()
{
    for(int a = 0, b = elements.size() ; a < b ; ++a)
    {
        if(elements[a]->is_deleted())
        {
            delete elements[a];
            elements.erase(elements.begin()+a);
            a--;
            b--;
            continue;
        }
        elements[a]->update();
    }
}

void Gui_manager::show()
{
    for(auto & a : elements)
    {
        a->show();
    }
}

}//end of gui namespace
