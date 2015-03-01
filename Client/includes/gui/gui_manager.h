#ifndef GUI_MANAGER_H_INCLUDED
#define GUI_MANAGER_H_INCLUDED

#include "gui_element.h"
#include <vector>

namespace gui
{

class Gui_manager : Gui_element
{
public:

    void add_element(Gui_element * added_element);
    void update()override;
    void show()override;


    Gui_manager();
    ~Gui_manager();

    Gui_manager(const Gui_manager &copied_object) = delete ;
    Gui_manager& operator=(const Gui_manager &copied_object) = delete ;
    Gui_manager(Gui_manager && moved_object) = delete ;
    Gui_manager& operator=(Gui_manager&& moved_object) = delete ;

private:

    std::vector< Gui_element * > elements;
    bool visible = true;
};

}
#endif // GUI_MANAGER_H_INCLUDED
