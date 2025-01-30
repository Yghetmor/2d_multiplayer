#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "utils.h"
#include <vector>
#include <bit>

class Player : public Entity
{
public:
    Player(SDL_Texture* texture);

    void update_position(Camera* camera);
    void handle_event(SDL_Event& e);
    double get_angle();
    std::vector<unsigned char> format_position();
    void reset_clicked();
    bool is_clicked();

private:
    static const unsigned int s_init_pos_x = MAP_WIDTH / 2;
    static const unsigned int s_init_pos_y = MAP_HEIGHT / 2;
    static const unsigned int s_width = 40;
    static const unsigned int s_height = 40;
    static const unsigned int s_velocity = 5;

    bool m_clicked{ false };
};

#endif // !PLAYER_H
