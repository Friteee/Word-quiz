#include "gui_element.h"

#include <vector>

namespace gui
{

template <typename Element> class List : public Gui_element
{
public :

    List(std::vector <Element> elements);
    void show()override;
    void update()override;

private :

    std::vector <Element> elements;
};

}//end of gui namespace
