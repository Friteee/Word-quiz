
#include "gaming_mode.h"
#include "game_logic.h"
#include "../gui/text.h"
#include <cstdlib>

namespace main_logic
{

/**
 * Gaming mode's input handler
 */

bool Gaming_mode::handle_input()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            return false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_q:
                break;
            case SDLK_a:
                break;
            case SDLK_w:
                break;
            case SDLK_s:
                break;
            case SDLK_d:
                break;
            case SDLK_RALT:
                break;
            case SDLK_LALT:
                break;
            case SDLK_TAB:
                break;
            case SDLK_BACKSPACE:
                if(input_word.size()>0)
                {
                    input_word.pop_back();
                    update_input();
                }

                break;
            case SDLK_ESCAPE:
                return false;
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            break;
        case SDL_WINDOWEVENT:
            switch(event.window.event)
            {
            case SDL_WINDOWEVENT_EXPOSED:
                break;
            case SDL_WINDOWEVENT_MOVED:
                break;
            }
            break;
        case SDL_MOUSEWHEEL:
            break;
        case SDL_TEXTINPUT:
            input_word += event.text.text;
            update_input();
            break;

        }
    }


    const Uint8 * key_states =SDL_GetKeyboardState(nullptr);

    // if alt + tab was pressed
    if((key_states[SDL_SCANCODE_LALT]||key_states[SDL_SCANCODE_RALT])&&key_states[SDL_SCANCODE_TAB])
    {
        // minimize the window
        video::Video_subsystem::minimize();
    }

    return true;
}

/**
 * Gaming mode's game loop
 */

bool Gaming_mode::run()
{

    // handle that input
    if(handle_input()==false)
    {
        return false;
    }
    // reload video subsystem
    video::Video_subsystem::reload();

    gui_manager.update();

    // main logic here
    main_background->show();

    if(input_word==word)
        change_word();

    SDL_Rect blit_location ;
    blit_location.w = video::Video_subsystem::get_width()/4;
    blit_location.h = video::Video_subsystem::get_width()/4;
    blit_location.x = video::Video_subsystem::get_width()/2 - blit_location.w/2;
    blit_location.y = video::Video_subsystem::get_height()/2 - blit_location.h;

    video::Video_subsystem::blit(word_image.get_texture() , nullptr , &blit_location);

    gui_manager.show();

    video::Video_subsystem::update_screen();

    return true;
}

/**
 * Constructor
 */

Gaming_mode::Gaming_mode(utility::Configuration * init_config):
    main_config(init_config),
    main_group( utility::Configuration("config/groups/banana.cfg"))
{
    main_background = new gui::Background(main_config->find_string("main_background").c_str());
    srand(SDL_GetTicks());

    int index = rand() % main_group.get_size();
    word = main_group.get_word(index);
    word_image = main_group.get_texture(index);
    main_group.delete_word(index);


    int word_x = 0;
    int word_y = 0;
    int text_size = 64;
    std::string empty_word (word.size(), '-');

    word_text = new gui::Text(init_config ,
                              empty_word,
                              word_x ,
                              word_y ,
                              text_size ,
                              SDL_Color{255,255,255,255}) ;

    word_x = video::Video_subsystem::get_width()/2 - word_text->get_width()/2;
    word_y = video::Video_subsystem::get_height()/2 + word_text->get_height();
    word_text->change_position(word_x,word_y);

    current_input = new gui::Text(init_config ,
                                  std::string(),
                                  word_x ,
                                  word_y ,
                                  text_size ,
                                  SDL_Color{255,255,255,255}) ;
    word_x = video::Video_subsystem::get_width()/2 - current_input->get_width()/2;
    word_y = video::Video_subsystem::get_height()/2 + word_text->get_height()*2;
    current_input->change_position(word_x,word_y);

    gui_manager.add_element(word_text);
    gui_manager.add_element(current_input);

    SDL_StartTextInput();

}

void Gaming_mode::change_word()
{
    if(main_group.get_size() == 0)
        return;
    int index = rand() % main_group.get_size();
    word = main_group.get_word(index);
    word_image = main_group.get_texture(index);
    main_group.delete_word(index);
    word_text->change_text(std::string( word.size() , '-' ));
    int word_x = video::Video_subsystem::get_width()/2 - word_text->get_width()/2;
    int word_y = video::Video_subsystem::get_height()/2 + word_text->get_height();
    word_text->change_position(word_x,word_y);
    input_word.clear();
    update_input();
}

void Gaming_mode::update_input()
{
    if(input_word.size()!=0)
        current_input->change_text(input_word);
    current_input->change_text(input_word);
    int word_x = video::Video_subsystem::get_width()/2 - current_input->get_width()/2;
    int word_y = video::Video_subsystem::get_height()/2 + current_input->get_height()*2;
    current_input->change_position(word_x,word_y);
}


}//end of main_logic namespace
