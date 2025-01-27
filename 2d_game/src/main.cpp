#include <cstdlib>
#include <cstring>
#include <iostream>
#include "game.h"
#include "online_game.h"

int main(int argc, char* args[])
{
    if (argc != 2 && argc != 3)
    {
        std::cout << "Need 1 or 2 arguments : offline, online <session id>" << std::endl;
        return -1;
    }

    if (strcmp(args[1], "offline") != 0 && strcmp(args[1], "online") != 0)
    {
        std::cout << "Arguments should be : offline, online <session id>" << std::endl;
        std::cout << "Got argument : " << args[1] << std::endl;
        return -1;
    }

    if (strcmp(args[1], "offline") == 0)
    {
        Game game;

        if (game.init("Offline Game", SCREEN_WIDTH, SCREEN_HEIGHT))
        {
            game.gameLoop();
        }

        game.shutdown();
        return 0;
    }

    if (strcmp(args[1], "online") == 0 && argc != 3)
    {
        std::cout << "Need a session id after \"online\" argument" << std::endl;
        return -1;
    }
    else 
    {
        int session_id = atoi(args[2]);
        if (session_id == 0)
        {
            std::cout << "Session_id must be a number other than 0" << std::endl;
            std::cout << "Got argument : " << args[2] << std::endl;
            return -1;
        }
        std::cout << "Connection to session : " << session_id << std::endl;

        OnlineGame game(session_id);

        if (game.init("Online Game", SCREEN_WIDTH, SCREEN_HEIGHT))
        {
            game.gameLoop();
        }

        game.shutdown();
        return 0;
    }
}
