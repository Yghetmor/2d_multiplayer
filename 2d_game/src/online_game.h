#ifndef ONLINE_GAME_H
#define ONLINE_GAME_H

#include "game.h"
#include "monster.h"
#include "projectile.h"

class OnlineGame : public Game {
public:
    OnlineGame(unsigned int instance_id);
    void gameLoop();
    void handleEvent();
    void unpack_positions(int socket);
    void unpack_monster(char** buf);
    void unpack_projectile(char** buf);
    void send_player_pos(int socket);

private:
    unsigned int m_instance_id;
};

#endif // !ONLINE_GAME_H
