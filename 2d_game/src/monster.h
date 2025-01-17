#ifndef MONSTER_H
#define MONSTER_H

#include "entity.h"
#include "player.h"

class Monster : public Entity
{
public:
    Monster(unsigned int init_x, unsigned int init_y, SDL_Texture* texture);

    void update_position(Player *player);

private:
    static const unsigned int s_width = 44;
    static const unsigned int s_height = 31;
    static const unsigned int s_velocity = 3;

};

#endif // !MONSTER_H
