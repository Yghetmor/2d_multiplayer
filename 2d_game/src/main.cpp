#include <iostream>
#include "game.h"

int main(int argc, char* args[])
{
	Game game;

	if (game.init("Game", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		game.gameLoop();
	}

	game.shutdown();
    return 0;
}
