#include "camera.h"
#include "utils.h"

void Camera::update(unsigned int player_x, unsigned int player_y, unsigned int player_width, unsigned int player_height)
{
    m_cam.x = ( player_x + player_width / 2 ) - SCREEN_WIDTH / 2;
    m_cam.y = ( player_y + player_height / 2 ) - SCREEN_HEIGHT / 2;

    if ( m_cam.x < 0 )
    {
        m_cam.x = 0;
    }
    if ( m_cam.y < 0 )
    {
        m_cam.y = 0;
    }
    if ( m_cam.x > MAP_WIDTH - m_cam.w )
    {
        m_cam.x = MAP_WIDTH - m_cam.w;
    }
    if ( m_cam.y > MAP_HEIGHT - m_cam.h )
    {
        m_cam.y = MAP_HEIGHT - m_cam.h;
    }
}

SDL_Rect* Camera::get_cam()
{
    return &m_cam;
}
