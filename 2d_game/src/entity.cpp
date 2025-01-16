#include "entity.h"
#include <SDL2/SDL_render.h>
#include <cmath>
#include <iostream>
#include "utils.h"

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

void Entity::update_position(Camera* camera)
{
    int mouse_x, mouse_y = 0;
    double calc_angle = 0.0;
    SDL_Rect* cam_rect = camera->get_cam();
    int normalized_x = m_pos_x - cam_rect->x;
    int normalized_y = m_pos_y - cam_rect->y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if (normalized_y == mouse_y)
    {
        if (normalized_x > mouse_x)
        {
            calc_angle = 270.0;
        }
        else 
        {
            calc_angle = 90.0;
        }
    }
    else 
    {
        if (normalized_x < mouse_x)
        {
            if (normalized_y < mouse_y)
            {
                double arctan = atan((double)(mouse_x - normalized_x) / (double)(mouse_y - normalized_y));
                calc_angle = 180.0 - (arctan * 180.0 / PI);
            }
            else 
            {
                double arctan = atan((double)(mouse_x - normalized_x) / (double)(normalized_y - mouse_y));
                calc_angle = arctan * 180.0 / PI;
            }
        }
        else 
        {
            if (normalized_y < mouse_y)
            {
                double arctan = atan((double)(normalized_x - mouse_x) / (double)(mouse_y - normalized_y));
                calc_angle = 180.0 + (arctan * 180.0 / PI);
            }
            else 
            {
                double arctan = atan((double)(normalized_x - mouse_x) / (double)(normalized_y - mouse_y));
                calc_angle = 360.0 - (arctan * 180.0 / PI);
            }
        }
    }

    if (calc_angle < 180.0)
    {
        m_angle = calc_angle + 180.0;
    }
    else 
    {
        m_angle = calc_angle - 180.0;
    }
}

void Entity::render(SDL_Renderer* renderer, Camera* camera)
{
    SDL_Rect render_rect = { (int)m_pos_x - camera->get_cam()->x, (int)m_pos_y - camera->get_cam()->y, (int)m_width, (int)m_height };
    SDL_RenderCopyEx(renderer, m_texture, nullptr, &render_rect, m_angle, nullptr, SDL_FLIP_NONE);
}
