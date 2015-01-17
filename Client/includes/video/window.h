#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include "window.h"

namespace video{

/**
 * Singleton pattern used here
 * Class to create video subsystem, which is used to
 * blit stuff to screen
 */
class Video_subsystem{

    public:

    // function to initialize video_subsystem
    static bool initialize_subsystem(int width, int height , bool fullscreen);
    // getter to access window
    SDL_Window* get_window();
    // getter to access renderer
    SDL_Renderer* get_renderer();
    // function to get the instance
    static Video_subsystem& get_instance();
    // blit texture to window
    static bool blit(SDL_Texture* texture , SDL_Rect* source , SDL_Rect* destination);
    // overload surface blit with angle and flip
    static bool blit(SDL_Texture* texture , SDL_Rect* source , SDL_Rect* destination , const double angle, const SDL_Point * center , const SDL_RendererFlip flip);
    // reload the window
    static bool reload();
    // update the screen
    static void update_screen();
    // minimize the window
    static void minimize();
    // set windows name
    static void set_programs_name(const char * name);
    // help create a texture
    static SDL_Texture* create_texture(SDL_Surface*);
    // draw line
    static void draw_line(int x_1 , int y_1 , int x_2 , int y_2, uint8_t r , uint8_t g, uint8_t b);


    private:

    // constructor
    Video_subsystem(int width, int height , bool fullscreen) ;
    // remove all other means to create video_subsystem
    Video_subsystem( Video_subsystem const& x) = delete;
    Video_subsystem &operator=( Video_subsystem const& x) = delete;
    Video_subsystem( Video_subsystem && x) = delete;
    Video_subsystem &operator=( Video_subsystem && x) = delete;
    // instance of video_subsystem
    static Video_subsystem* instance;
    // main window to blit stuff into
    SDL_Window* main_window = nullptr;
    // renderer to help blit stuff
    SDL_Renderer* main_renderer = nullptr;
    // bool to know if the instance was created without errors
    bool is_created;
};



}

#endif // WINDOW_H
