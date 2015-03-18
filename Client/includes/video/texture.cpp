
#include "texture.h"
#include "window.h"
#include <assert.h>
#include <cstdio>

namespace video
{

Texture::Texture()
{
    // "Nope. Sorry. Nothing"
}

/**
 * Initialize texture with file
 */

void Texture::init(std::string filename)
{
    reset();
    create_surface(filename);
    create_texture(filename);
}

/**
 * Initialize texture with filename and rgb color key
 */
void Texture::init(std::string filename, SDL_Color color_key)
{
    reset();
    create_surface(filename);
    Uint32 key = SDL_MapRGB((*surface)->format,color_key.r,color_key.g,color_key.b);
    SDL_SetColorKey( *surface , SDL_TRUE , key );
    create_texture(filename);
}

/**
 * Initialize texture with a surface
 */
void Texture::init(SDL_Surface * init_surface)
{
    reset();
    if(!init_surface)
    {
        printf("Error : null pointer passed to texture");
        assert(1);
    }
    surface = std::make_shared<SDL_Surface*>(init_surface);
    create_texture(std::string("(Surface has no filename)"));
}

/**
 * Initialize texture with a surface
 */
void Texture::init(std::string text, SDL_Color text_color, TTF_Font * font)
{
    if(surface.unique())
    {
        SDL_DestroyTexture(*texture);
        SDL_FreeSurface(*surface);
    }
    texture.reset();
    surface.reset();
    surface = std::make_shared<SDL_Surface*>(TTF_RenderText_Blended( font, text.c_str(), text_color ));
    create_texture(std::string("Surface is text"));
}

Texture::Texture(Texture const & copied)
{
    surface = copied.surface;
    texture = copied.texture;
}

Texture::Texture(Texture && moved)
{
    surface = moved.surface;
    texture = moved.texture;
    moved.surface.reset();
    moved.texture.reset();
}

Texture& Texture::operator=(Texture const & copied)
{
    surface = copied.surface;
    texture = copied.texture;
    return *this;
}

Texture& Texture::operator=(Texture && moved)
{
    surface = moved.surface;
    texture = moved.texture;
    moved.surface.reset();
    moved.texture.reset();

    return *this;
}

/**
 * Surface, texture, width and height getters
 */
SDL_Texture * Texture::get_texture()
{
    if(!texture)
    {
        printf("Warning : nullptr texture is being passed\n");
        printf("Did you forget to initialize texture?\n");
    }
    return *texture;
}

SDL_Surface * Texture::get_surface()
{
    if(!surface)
    {
        printf("Warning : nullptr surface is being passed\n");
        printf("Did you forget to initialize texture?\n");
    }
    return *surface;
}

Texture::~Texture()
{
    if(surface.unique())
    {
        SDL_FreeSurface(*surface);
    }
    if(texture.unique())
    {
        SDL_DestroyTexture(*texture);
    }
    surface.reset();
    texture.reset();
}

unsigned int Texture::get_height()
{
    return (*surface)->h;
}

unsigned int Texture::get_width()
{
    return (*surface)->w;
}

void Texture::set_alpha(unsigned int alpha)
{
    if(alpha>255)
        printf("Warning! Alpha passed to texture is more than 255");
    SDL_SetTextureAlphaMod(*texture, alpha);
}

void Texture::create_surface(std::string filename)
{
    SDL_Surface * init_surface = SDL_LoadBMP(filename.c_str());
    surface = std::make_shared<SDL_Surface*>(init_surface);
    if(!init_surface)
    {
        printf("Error : Error creating surface from %s \n", filename.c_str());
        printf("Error code : %s\n",SDL_GetError());
        assert(1);
    }
}

void Texture::create_texture(std::string filename)
{
    SDL_Texture * init_texture = Video_subsystem::create_texture(*surface);
    texture = std::make_shared<SDL_Texture*>(init_texture);
    if(init_texture == nullptr)
    {
        printf("Error : Error creating texture from %s \n", filename.c_str());
        printf("Possible causes - No renderer present \n");
        printf("Error code : %s\n",SDL_GetError());
        assert(1);
    }
    else
    {
        SDL_SetTextureBlendMode(*texture,SDL_BLENDMODE_BLEND);
    }
}

void Texture::reset()
{
    if(surface.unique())
    {
        SDL_FreeSurface(*surface);
    }
    if(texture.unique())
    {
        SDL_DestroyTexture(*texture);
    }
    surface.reset();
    texture.reset();
}

}// end of video namespace
