#ifndef GUI_MANAGER_H_INCLUDED
#define GUI_MANAGER_H_INCLUDED

#include "gui_element.h"
#include <vector>

namespace gui
{

class Gui_manager
{
public:

    void add_element(Gui_element * added_element);
    void update();
    void show();
    void handle_click(int x, int y);


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
