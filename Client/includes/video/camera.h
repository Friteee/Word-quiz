#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <SDL.h>

namespace video
{

/**
 * Singleton class to handle players camera and all that stuff
 */

class Camera
{
    public:

    // blit function for textures
    static bool blit(SDL_Texture* texture , SDL_Rect* source , SDL_Rect* location);
    // blit function for textures
    static bool blit(SDL_Texture* texture , SDL_Rect* source , SDL_Rect* location , const double angle, const SDL_Point * center , const SDL_RendererFlip flip);
    // camera getter
    static Camera& get_instance();
    // set position for camera
    static void set_position(int init_x , int init_y);
    // overload set_position
    static void set_position(SDL_Rect init_location);
    // initialize subsystem
    static bool initialize(int init_width , int init_height , int init_x , int init_y);
    // overloading initialize
    static bool initialize(SDL_Rect init_location);
    // increase and decrease zoom
    static void change_zoom(int amount);
    // zoom setter
    static void set_zoom(double amount);
    // moving the camera
    static void move(int x , int y);
    // get position
    inline static SDL_Rect get_position(){return instance->location;}
    // get zoom
    inline static double get_zoom(){return instance->zoom;}

    private:
    // private constructor
    Camera(int init_width , int init_height , int init_x , int init_y);
    // deleted move and copy constructors
    Camera(Camera const& x) = delete;
    Camera& operator=(Camera const& x) = delete;
    Camera(Camera&& x) = delete;
    Camera& operator=(Camera&& x) = delete;
    // x and y of camera position, in pixels
    SDL_Rect location;
    // instance of the camera
    static Camera* instance;
    // zoom amount
    double zoom; //zoom level
};

}// end of video namespace

#endif // CAMERA_H_INCLUDED
