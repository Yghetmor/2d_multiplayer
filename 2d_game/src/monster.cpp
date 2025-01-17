#include "monster.h"

Monster::Monster(unsigned int init_x, unsigned int init_y, SDL_Texture* texture)
    : Entity{init_x, init_y, s_width, s_height, s_velocity, texture} {}
