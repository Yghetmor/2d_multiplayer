#ifndef ONLINE_GAME_H
#define ONLINE_GAME_H

#include "game.h"

class OnlineGame : public Game {
public:
    OnlineGame(unsigned int instance_id);
    void gameLoop();
    void handleEvent();

private:
    unsigned int m_instance_id;
};

#endif // !ONLINE_GAME_H
