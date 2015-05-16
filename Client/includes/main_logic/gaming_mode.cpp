
#include "gaming_mode.h"
#include "main_menu_mode.h"
#include "game_logic.h"
#include "../gui/progress_bar.h"
#include <cstdlib>
#include <sstream>

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

    bool quit = false;
    if(input_word==word)
        quit = change_word();
    if(quit)
        Game_logic::set_current_mode (new Main_menu_mode (main_config) );

    std::stringstream ss;
    ss <<"Time : "<<score_stopwatch.get_ticks()/1000;
    score->change_text(ss.str());

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

Gaming_mode::Gaming_mode(utility::Configuration * init_config , std::string filename):
    main_config(init_config),
    main_group( utility::Configuration(filename))
{
    music.stop();
    music.init("sound/tetris.mp3");
    music.play();
    score_stopwatch.start();
    applause.init(std::string ("sound/pop.wav"));
    // init background and randomness
    main_background = new gui::Background(main_config->find_string("main_background").c_str());
    srand(SDL_GetTicks());

    //get a random word
    int index = rand() % main_group.get_size();
    word = main_group.get_word(index);
    word_image = main_group.get_texture(index);
    main_group.delete_word(index);

    // make a '------' out of a words size
    int word_x = 0;
    int word_y = 0;
    int text_size = 64;
    std::string empty_word (word.size(), '-');

    //initialize '--------'
    letters_available = empty_word;
    word_text = new gui::Text(init_config ,
                              empty_word,
                              word_x ,
                              word_y ,
                              text_size ,
                              SDL_Color {255,255,255,255}) ;

    word_x = video::Video_subsystem::get_width()/2 - word_text->get_width()/2;
    word_y = video::Video_subsystem::get_height()/2 + word_text->get_height();
    word_text->change_position(word_x,word_y);

    // initialize input visualization
    current_input = new gui::Text(init_config ,
                                  std::string(),
                                  word_x ,
                                  word_y ,
                                  text_size ,
                                  SDL_Color {255,255,255,255}) ;
    word_x = video::Video_subsystem::get_width()/2 - current_input->get_width()/2;
    word_y = video::Video_subsystem::get_height()/2 + word_text->get_height()*2;
    current_input->change_position(word_x,word_y);

    // initialize progress bar and its location
    SDL_Rect progress_bar_location;
    progress_bar_location.w = video::Video_subsystem::get_width() / 6;
    progress_bar_location.h = video::Video_subsystem::get_height() / 12;
    progress_bar_location.x = video::Video_subsystem::get_width() - progress_bar_location.w - 20;
    progress_bar_location.y = video::Video_subsystem::get_height() - progress_bar_location.h - 20;
    progress_bar = new gui::Progress_bar(5000 , progress_bar_location);
    auto progress_function = [this]()
    {
        this->reveal_letter();
    };
    progress_bar->set_function(progress_function);
    progress_bar->start();
    // initialize score visualization
    word_x = 20;
    word_y = 0;
    score = new gui::Text(init_config ,
                          std::string("Score = 0"),
                          word_x,
                          word_y,
                          text_size ,
                          SDL_Color {255,255,255,255}) ;
    word_y = video::Video_subsystem::get_height() - score->get_height() - 20;
    score->change_position(word_x, word_y);

    //add everything to gui manager
    gui_manager.add_element(score);
    gui_manager.add_element(word_text);
    gui_manager.add_element(current_input);
    gui_manager.add_element(progress_bar);
    //start input
    SDL_StartTextInput();

}

bool Gaming_mode::change_word()
{
    if(main_group.get_size() == 0)
        return true;
    // get random word
    int index = rand() % main_group.get_size();
    word = main_group.get_word(index);
    word_image = main_group.get_texture(index);
    main_group.delete_word(index);
    // change size of '------'s
    letters_available = std::string( word.size() , '-' );
    word_text->change_text(letters_available);
    // change their location
    int word_x = video::Video_subsystem::get_width()/2 - word_text->get_width()/2;
    int word_y = video::Video_subsystem::get_height()/2 + word_text->get_height();
    word_text->change_position(word_x,word_y);
    //clear input
    input_word.clear();
    update_input();
    //reset progress bar
    progress_bar->reset();
    applause.play();
    return false;
}

void Gaming_mode::update_input()
{
    current_input->change_text(input_word);
    int word_x = video::Video_subsystem::get_width()/2 - current_input->get_width()/2;
    int word_y = video::Video_subsystem::get_height()/2 + current_input->get_height()*2;
    current_input->change_position(word_x,word_y);
}

void Gaming_mode::reveal_letter()
{
    if(letters_available.find('-')==std::string::npos)
        return;
    //get random letter
    int index = rand() % letters_available.length();
    while(letters_available[index]!='-')
    {
        index = rand() % letters_available.length();
    }
    letters_available[index] = word[index];
    word_text->change_text(letters_available);
}

}//end of main_logic namespace
