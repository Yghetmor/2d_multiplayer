#include "map.h"

void Map::render(SDL_Renderer* renderer, Camera* camera)
{
    SDL_RenderCopy(renderer, m_texture, camera->get_cam(), nullptr);
}
