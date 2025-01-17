#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"
#include "player.h"

class Projectile : public Entity
{
public:
    Projectile(Player *shooter, SDL_Texture *texture);
    ~Projectile();

    void update_position();
    bool is_alive();

private:
    static const unsigned int s_width = 6;
    static const unsigned int s_height = 16;
    static const unsigned int s_velocity = 10;

    bool m_alive;

};

#endif // !PROJECTILE_H
