#ifndef MAP_H
#define MAP_H

#include "utils.h"
#include "camera.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

class Map 
{
public:

    static const int height = MAP_HEIGHT;
    static const int width = MAP_WIDTH;

    Map(SDL_Texture* texture)
        : m_texture{texture} {}

    ~Map() { SDL_DestroyTexture(m_texture); }

    void render(SDL_Renderer* renderer, Camera* camera);

private:
    SDL_Texture* m_texture;

};

#endif // !MAP_H
