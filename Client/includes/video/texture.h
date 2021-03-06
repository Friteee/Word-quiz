#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>

namespace video
{


/**
 * SDL_Texture and SDL_Surface wrapper
 */
class Texture
{

public:
    Texture();
    Texture           (const Texture & copied);
    Texture& operator=(const Texture & copied);
    Texture           (Texture && moved);
    Texture& operator=(Texture && moved);
    void         init(std::string filename);
    void         init(std::string filename, SDL_Color color_key);
    void         init(SDL_Surface * init_surface);
    void         init(std::string text, SDL_Color text_color , TTF_Font * font);
    void         set_alpha(unsigned int alpha);
    SDL_Texture* get_texture();
    SDL_Surface* get_surface();
    unsigned int get_width();
    unsigned int get_height();
    void         set_angle(int init_angle);
    int          get_angle();
    ~Texture();

private:

    void create_surface(std::string filename);
    void create_texture(std::string filename);
    void reset();
    std::shared_ptr<SDL_Surface*> surface;
    std::shared_ptr<SDL_Texture*> texture;
    int angle;
};

}// end of video namespace

#endif // TEXTURE_H_INCLUDED
