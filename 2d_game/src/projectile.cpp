#include "projectile.h"

Projectile::Projectile(Player *shooter, SDL_Texture *texture)
    : Entity{shooter->get_x() + shooter->get_width() / 2, shooter->get_y() + shooter->get_height() / 2, s_width, s_height, s_velocity, texture}, m_alive{true} 
{
    m_angle = shooter->get_angle();
    double calc_angle = 0.0;

    if (m_angle < 180.0)
    {
        calc_angle = m_angle + 180.0;
    }
    else 
    {
        calc_angle = m_angle - 180.0;
    }

    m_vel_x = m_entity_velocity * sin(calc_angle * PI / 180.0);
    m_vel_y = (-1.0) * m_entity_velocity * cos(calc_angle * PI / 180.0);
}

Projectile::~Projectile() 
{
    m_texture = nullptr;
}

void Projectile::update_position()
{
    m_pos_x += m_vel_x;
    m_pos_y += m_vel_y;

    if (m_pos_x < 50 || m_pos_x > MAP_WIDTH - 50 - m_width || m_pos_y < 50 || m_pos_y > MAP_HEIGHT - 50 - m_height)
    {
        m_alive = false;
    }

    m_rect.x = m_pos_x;
    m_rect.y = m_pos_y;
}

bool Projectile::is_alive()
{
    return m_alive;
}
