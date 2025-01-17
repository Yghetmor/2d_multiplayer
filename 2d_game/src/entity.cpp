#include "entity.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include "utils.h"

Entity::Entity(unsigned int pos_x, unsigned int pos_y, unsigned int width, unsigned int height, unsigned int velocity, SDL_Texture* texture)
    : m_pos_x{(pos_x - (float)width / 2)}, m_pos_y{pos_y - (float)height / 2}, m_width{width}, m_height{height}, m_entity_velocity{velocity}, m_vel_x{0}, m_vel_y{0}, m_texture{texture}
{
    m_rect = SDL_Rect{ (int)(pos_x - width / 2), (int)(pos_y - height / 2), (int)width, (int)height };
}

Entity::~Entity()
{
    if ( m_texture != nullptr)
    {
        SDL_DestroyTexture( m_texture );
        m_texture = nullptr;
    }
}

void Entity::render(SDL_Renderer* renderer, Camera *camera)
{
    SDL_Rect *camera_rect = camera->get_cam();
    SDL_Rect render_rect = { (int)m_pos_x - camera_rect->x, (int)m_pos_y - camera_rect->y, (int)m_width, (int)m_height };
    SDL_RenderCopyEx(renderer, m_texture, nullptr, &render_rect, m_angle, nullptr, SDL_FLIP_NONE);
}
