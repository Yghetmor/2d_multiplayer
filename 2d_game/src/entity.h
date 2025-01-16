#ifndef ENTITY_H
#define ENTITY_H

#include "camera.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
public:
    Entity(unsigned int pos_x, unsigned int pos_y, unsigned int width, unsigned int height, SDL_Texture* texture);
    ~Entity();

    void update_position(Camera* camera);
    void render(SDL_Renderer* renderer, Camera* camera);
    unsigned int get_x() { return m_pos_x; }
    unsigned int get_y() { return m_pos_y; }

protected:
    unsigned int m_pos_x, m_pos_y;
    unsigned int m_width, m_height;
    double m_angle = 0;
    int m_vel_x, m_vel_y;

    SDL_Rect m_rect;
    SDL_Texture* m_texture;
};

#endif // !ENTITY_H
