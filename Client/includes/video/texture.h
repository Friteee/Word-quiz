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
    Texture(const Texture & copied);
    Texture& operator=(const Texture & copied);
    Texture(Texture && moved);
    Texture& operator=(Texture && moved);
    void         init(std::string filename);
    void         init(std::string filename, SDL_Color color_key);
    void         init(SDL_Surface * init_surface);
    void         init(std::string text, SDL_Color text_color , TTF_Font * font);
    SDL_Texture* get_texture();
    SDL_Surface* get_surface();
    unsigned int get_width();
    unsigned int get_height();
    ~Texture();

    private:

    std::shared_ptr<SDL_Surface*> surface;
    std::shared_ptr<SDL_Texture*> texture;
};

}// end of video namespace

#endif // TEXTURE_H_INCLUDED
