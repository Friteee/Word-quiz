#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include "gui_element.h"

namespace gui
{

class Table : public Gui_element
{
public:
    Table(int x , int y);
    void                                     init();
    void                                     show()override;
    void                                     update()override;
    void                                     handle_click(int x, int y)override;
    std::vector<std::string> &               operator[](unsigned int index);
    void                                     set_rows(unsigned int size);
    void                                     set_columns(unsigned int size);
    video::Texture &                         get_texture();
private:
    std::vector <std::vector<std::string > > table_info;

};

}//end of gui namespace

#endif // TABLE_H_INCLUDED
