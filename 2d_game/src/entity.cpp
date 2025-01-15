#include "entity.h"

Entity::Entity(unsigned int pos_x, unsigned int pos_y, unsigned int width, unsigned int height, SDL_Texture* texture)
    : m_pos_x{pos_x - width / 2}, m_pos_y{pos_y - height / 2}, m_width{width}, m_height{height}, m_vel_x{0}, m_vel_y{0}, m_texture{texture}
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

void Entity::render(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, m_texture, nullptr, &m_rect, 0, nullptr, SDL_FLIP_NONE);
}
