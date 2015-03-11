

#include "gui_manager.h"
#include "click.h"
#include <cstdio>

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
    gui::Click click;
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

        if(click.has_clicked())
        {
            int x , y;

            click.get_location(x,y);

            elements[a]->handle_click(x,y);
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
