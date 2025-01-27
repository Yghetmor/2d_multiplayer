#include "player.h"
#include <cstdint>

Player::Player(SDL_Texture* texture)
    : Entity{s_init_pos_x, s_init_pos_y, s_width, s_height, s_velocity, texture} {}

void Player::update_position(Camera* camera)
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

    if (m_vel_x != 0 && m_vel_y != 0)
    {
        m_pos_x += (float)m_vel_x * COS_45;
        m_pos_y += (float)m_vel_y * COS_45;
    }
    else
    {
        m_pos_x += m_vel_x;
        m_pos_y += m_vel_y;
    }

    if (m_pos_x < 50)
    {
        m_pos_x = 50;
    }
    else if (m_pos_x > MAP_WIDTH - 50 - m_width)
    {
        m_pos_x = MAP_WIDTH - 50 - m_width;
    }

    if (m_pos_y < 50)
    {
        m_pos_y = 50;
    }
    else if (m_pos_y > MAP_HEIGHT - 50 - m_height)
    {
        m_pos_y = MAP_HEIGHT - 50 - m_height;
    }

    m_rect.x = m_pos_x;
    m_rect.y = m_pos_y;
}

void Player::handle_event(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w: m_vel_y -= m_entity_velocity; break;
            case SDLK_s: m_vel_y += m_entity_velocity; break;
            case SDLK_a: m_vel_x -= m_entity_velocity; break;
            case SDLK_d: m_vel_x += m_entity_velocity; break;
        }
    }

    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w: m_vel_y += m_entity_velocity; break;
            case SDLK_s: m_vel_y -= m_entity_velocity; break;
            case SDLK_a: m_vel_x += m_entity_velocity; break;
            case SDLK_d: m_vel_x -= m_entity_velocity; break;
        }
    }
}

double Player::get_angle()
{
    return m_angle;
}

std::vector<char> Player::format_position()
{
    std::vector<char> output;
    uint16_t pos_x = static_cast<uint16_t>(m_pos_x);
    uint16_t pos_y = static_cast<uint16_t>(m_pos_y);
    float angle = static_cast<float>(angle);

    if (std::endian::native == std::endian::little)
    {
        char *byte = (char*)&pos_x;
        for (size_t i{}; i < sizeof(pos_x); i++)
        {
            output.push_back(*byte);
            byte++;
        }

        byte = (char*)&pos_y;
        for (size_t i{}; i < sizeof(pos_y); i++)
        {
            output.push_back(*byte);
            byte++;
        }

        byte = (char*)&angle;
        for (size_t i{}; i < sizeof(angle); i++)
        {
            output.push_back(*byte);
            byte++;
        }
    }
    else 
    {

    }
    return output;
}
