#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "text.h"
#include "gui_element.h"
#include "../utility/configuration.h"
#include <string>

namespace gui
{

class Text : public Gui_element
{
    public:

    Text(utility::Configuration * config, std::string init_text , int x , int y, SDL_Color init_color_key);
    void show() override;
    void update() override;
    void change_text(std::string init_text);

    private:

    std::string text;
    TTF_Font * font;
    SDL_Color color_key;

};

}

#endif // TEXT_H_INCLUDED
