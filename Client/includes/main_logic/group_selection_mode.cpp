
#include "group_selection_mode.h"
#include "game_logic.h"
#include "../gui/button.h"
#include "../gui/click.h"
#include "../audio/music.h"
#include "../utility/functions.h"


namespace main_logic
{

/**
 * Group_selection's input handler
 */

bool Group_selection_mode::handle_input()
{
    gui::Click click;
    click.set_clicked(false);
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
            case SDLK_ESCAPE:
                return false;
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            click.set_clicked(false);
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                click.set_location(event.button.x,event.button.y);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            click.set_clicked(true);
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                click.set_location(event.button.x,event.button.y);
            }
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
 * Group selection mode's game loop
 */

bool Group_selection_mode::run()
{
    // handle that input
    if(handle_input()==false)
    {
        return false;
    }

    main_gui.update();

    // reload video subsystem
    video::Video_subsystem::reload();
    // main logic here
    main_background->show();
    main_gui.show();
    video::Video_subsystem::update_screen();
    // check the fps and sleep the necessary time

    return true;
}

/**
 * Constructor
 */

Group_selection_mode::Group_selection_mode(utility::Configuration * init_config):
    main_config(init_config),
    groups(std::string("./config/")+main_config->find_string("group_config"))
{
    position = 0;

    std::vector<std::string> group_string_buffer = groups.find_strings("group");

    for(std::string  a : group_string_buffer)
    {
        std::vector<std::string> another_buffer = utility::get_separated_strings(a);
        group_names.push_back(another_buffer[0]);
        video::Texture image_buffer;
        image_buffer.init(another_buffer[1]);
        group_images.push_back(image_buffer);
    }

    gui::Button * visible_group;
    gui::Button * next_group;
    gui::Button * previous_group;
    gui::Button * decrease_volume;
    gui::Button * increase_volume;

    visible_group = new gui::Button(100,100);
    visible_group->init_image(group_images[position]);
    visible_group->set_width(video::Video_subsystem::get_width() / 2);
    visible_group->set_height(video::Video_subsystem::get_height() / 2);
    visible_group->change_position(video::Video_subsystem::get_width() / 2 - visible_group->get_width() / 2 , video::Video_subsystem::get_height() / 2 - visible_group->get_height()/2);
    auto visible_group_function = [this]()
    {
        main_logic::Game_logic::set_current_mode( new Gaming_mode (main_config , group_names[position]) );
    };
    visible_group->init_function(visible_group_function);

    next_group = new gui::Button(100,100);
    next_group->init_image(main_config->find_string("left_arrow"));
    next_group->set_width(video::Video_subsystem::get_width() / 6);
    next_group->change_position(video::Video_subsystem::get_width()-next_group->get_width(),video::Video_subsystem::get_height()/2-next_group->get_height()/2);
    auto next_function = [this,visible_group]()
    {
        if(position + 1 >= group_names.size())
            return;
        else
            position++;

        visible_group->init_image(group_images[position]);
        visible_group->set_width(video::Video_subsystem::get_width() / 2);
        visible_group->set_height(video::Video_subsystem::get_height() / 2);
        visible_group->change_position(video::Video_subsystem::get_width() / 2 - visible_group->get_width() / 2 , video::Video_subsystem::get_height() / 2 - visible_group->get_height()/2);

    };
    next_group->init_function(next_function);

    previous_group = new gui::Button(100,100);
    previous_group->init_image(main_config->find_string("left_arrow"));
    previous_group->get_texture().set_angle(180);
    previous_group->set_width(video::Video_subsystem::get_width() / 6);
    previous_group->change_position(0,video::Video_subsystem::get_height()/2-previous_group->get_height()/2);
    auto previous_function = [this,visible_group]()
    {
        if(position - 1 > group_names.size())
            return;
        else
            position--;

        visible_group->init_image(group_images[position]);
        visible_group->set_width(video::Video_subsystem::get_width() / 2);
        visible_group->set_height(video::Video_subsystem::get_height() / 2);
        visible_group->change_position(video::Video_subsystem::get_width() / 2 - visible_group->get_width() / 2 , video::Video_subsystem::get_height() / 2 - visible_group->get_height()/2);
    };
    previous_group->init_function(previous_function);

    decrease_volume = new gui::Button(100,100);
    decrease_volume->init_image(main_config->find_string("decrease_volume"));
    decrease_volume->change_position(video::Video_subsystem::get_width() - 3 * decrease_volume->get_width() ,decrease_volume->get_height()/2);
    auto decrease_volume_function = []()
    {
        audio::Music::change_volume(-10);
    };
    decrease_volume->init_function(decrease_volume_function);

    increase_volume = new gui::Button(100,100);
    increase_volume->init_image(main_config->find_string("increase_volume"));
    increase_volume->change_position(video::Video_subsystem::get_width() - 1.5 * increase_volume->get_width() ,increase_volume->get_height()/2);
    auto increase_volume_function = []()
    {
        audio::Music::change_volume(10);
    };
    increase_volume->init_function(increase_volume_function);

    main_gui.add_element(next_group);
    main_gui.add_element(previous_group);
    main_gui.add_element(decrease_volume);
    main_gui.add_element(increase_volume);
    main_gui.add_element(visible_group);

    main_background = new gui::Background(main_config->find_string("main_background").c_str());
}

}// end of main_logic namespace
