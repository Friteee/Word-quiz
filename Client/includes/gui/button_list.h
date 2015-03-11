#include "gui_element.h"
#include "text_button.h"
#include <vector>

namespace gui
{

class Button_list : public Gui_element
{
public :

    Button_list();
    ~Button_list();
    void add_button(Text_button * button);
    void show()override;
    void update()override;
    void handle_click(int x, int y)override;

private :

    std::vector <Text_button*> elements;
};

}//end of gui namespace
