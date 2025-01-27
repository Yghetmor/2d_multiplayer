#ifndef MONSTER_H
#define MONSTER_H

#include "entity.h"
#include "player.h"

class Monster : public Entity
{
public:
    Monster(unsigned int init_x, unsigned int init_y, SDL_Texture* texture);
    Monster(unsigned int pos_x, unsigned int pos_y, SDL_Texture *texture, double angle, int health);
    ~Monster();

    void update_position(Player *player);
    void receive_damage(unsigned int damage);
    int get_health();

private:
    static const unsigned int s_width = 44;
    static const unsigned int s_height = 31;
    static const unsigned int s_velocity = 3;
    int m_health = 3;

};

#endif // !MONSTER_H
