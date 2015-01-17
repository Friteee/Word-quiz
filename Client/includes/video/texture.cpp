

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
    if(surface.unique())
    {
        SDL_DestroyTexture(*texture);
        SDL_FreeSurface(*surface);

    }
    surface.reset();
    texture.reset();
    surface = std::make_shared<SDL_Surface*>(SDL_LoadBMP(filename.c_str()));
    if(!surface)
    {
        printf("Error : Error creating surface from %s \n", filename.c_str());
        printf("Error code : %s\n",SDL_GetError());
        assert(1);
    }
    texture = std::make_shared<SDL_Texture*>(Video_subsystem::create_texture(*surface));
    if(!texture)
    {
        printf("Error : Error creating texture from %s \n", filename.c_str());
        printf("Possible causes - No renderer present \n");
        printf("Error code : %s\n",SDL_GetError());
        assert(1);
    }
}

/**
 * Initialize texture with filename and rgb color key
 */
void Texture::init(std::string filename, SDL_Color color_key)
{
    if(surface.unique())
    {
        SDL_DestroyTexture(*texture);
        SDL_FreeSurface(*surface);

    }
    surface.reset();
    texture.reset();
    surface = std::make_shared<SDL_Surface*>(SDL_LoadBMP(filename.c_str()));
    if(!surface)
    {
        printf("Error : Error creating surface from %s \n", filename.c_str());
        printf("Error code : %s\n",SDL_GetError());
        assert(1);
    }
    Uint32 key = SDL_MapRGB((*surface)->format,color_key.r,color_key.g,color_key.b);
    SDL_SetColorKey( *surface , SDL_TRUE , key );
    texture = std::make_shared<SDL_Texture*>(Video_subsystem::create_texture(*surface));
    if(!texture)
    {
        printf("Error : Error creating texture from %s \n", filename.c_str());
        printf("Possible causes - No renderer present \n");
        printf("Error code : %s\n",SDL_GetError());
        assert(1);
    }
}

/**
 * Initialize texture with a surface
 */
void Texture::init(SDL_Surface * init_surface)
{
    if(surface.unique())
    {
        SDL_DestroyTexture(*texture);
        SDL_FreeSurface(*surface);

    }
    if(!init_surface)
    {
        printf("Error : null pointer passed to texture");
        assert(1);
    }
    surface = std::make_shared<SDL_Surface*>(init_surface);
    texture = std::make_shared<SDL_Texture*>(Video_subsystem::create_texture(*surface));
    if(!texture)
    {
        printf("Error : Error creating texture from passed surface \n");
        printf("Possible causes - No renderer present \n");
        printf("Error code : %s\n",SDL_GetError());
        assert(1);
    }
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
    texture = std::make_shared<SDL_Texture*>(Video_subsystem::create_texture(*surface));
    if(!texture)
    {
        printf("Error : Error creating texture from passed surface \n");
        printf("Possible causes - No renderer present \n");
        printf("Error code : %s\n",SDL_GetError());
        assert(1);
    }
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
    if(moved.surface.unique())
    {
        SDL_DestroyTexture(*texture);
        SDL_FreeSurface(*surface);
    }
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



}// end of video namespace
