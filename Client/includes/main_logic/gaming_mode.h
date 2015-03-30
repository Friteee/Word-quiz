#ifndef GAMING_MODE_H_INCLUDED
#define GAMING_MODE_H_INCLUDED

#include "program_mode.h"
#include "../gui/background.h"
#include "../gui/gui_manager.h"
#include "../game/word_group.h"
#include "../video/texture.h"
#include "../gui/text.h"

namespace gui
{
    class Progress_bar;
}

#include <string>

namespace main_logic
{

class Gaming_mode : public Program_mode
{
public :

    Gaming_mode(utility::Configuration * init_config);
    bool run ()override;
    bool handle_input()override;

private:
    void update_input();
    // change word function
    bool change_word();
    // reveal letter
    void reveal_letter();
    // background
    gui::Background        * main_background;
    // event
    SDL_Event                event;
    // configuration
    utility::Configuration * main_config;
    // word group
    game::Word_group         main_group;
    // texture of the word
    video::Texture           word_image;
    // gui elements manager
    gui::Gui_manager         gui_manager;
    // word we are trying to guess
    std::string              word;
    // available word
    std::string              letters_available;
    // help to guess the word
    gui::Text              * word_text;
    // current word input
    gui::Text              * current_input;
    // score
    gui::Text              * score;
    // progress bar
    gui::Progress_bar      * progress_bar;
    // input word
    std::string              input_word;
    // score
    int current_score;
    // add score
    int added_score;
};

}

#endif // GAMING_MODE_H_INCLUDED
