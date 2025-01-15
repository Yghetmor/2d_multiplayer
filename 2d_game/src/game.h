#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "clock.h"
#include "utils.h"

class Game
{
public:
	bool init(const char* title, int width, int height);
	void gameLoop();
	void shutdown();
	SDL_Texture* loadTexture(const char* path);

private:
	void handleEvent();
	void update();
	void draw();

	bool isRunning{ true };

	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
	Clock* m_clock;

	bool isPaused{ false };
};

#endif // !GAME_H
