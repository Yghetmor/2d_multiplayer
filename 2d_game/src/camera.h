#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "utils.h"

class Camera 
{
public:

    void update();
    SDL_Rect* get_cam();

private:

    SDL_Rect m_cam = { (MAP_WIDTH - SCREEN_WIDTH) / 2, (MAP_HEIGHT - SCREEN_HEIGHT) / 2, SCREEN_WIDTH, SCREEN_HEIGHT };

};

#endif // !CAMERA_H
