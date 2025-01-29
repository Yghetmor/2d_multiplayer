#include "monster.h"
#include <cmath>

Monster::Monster(unsigned int init_x, unsigned int init_y, SDL_Texture* texture)
    : Entity{init_x, init_y, s_width, s_height, s_velocity, texture} {}

Monster::Monster(unsigned int pos_x, unsigned int pos_y, SDL_Texture *texture, double angle, int health)
    : Entity{pos_x, pos_y, s_width, s_height, s_velocity, texture} 
{
    m_angle = angle;
    m_health = health;
}

Monster::~Monster()
{
    m_texture = nullptr;
}

void Monster::update_position(Player *player)
{
    float player_x = player->get_x();
    float player_y = player->get_y();
    double calc_angle = 0.0;

    if (m_pos_y == player_y)
    {
        if (m_pos_x > player_x)
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
        double arctan = atan((double)(player_x - m_pos_x) / (double)(m_pos_y - player_y));
        calc_angle = arctan * 180.0 / PI;

        if (m_pos_y < player_y)
        {
            calc_angle += 180.0;
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

    m_vel_x = m_entity_velocity * sin(calc_angle * PI / 180.0);
    m_vel_y = (-1.0) * m_entity_velocity * cos(calc_angle * PI / 180.0);

    m_pos_x += m_vel_x;
    m_pos_y += m_vel_y;

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

void Monster::receive_damage(unsigned int damage)
{
    m_health -= damage;
}

int Monster::get_health()
{
    return m_health;
}
