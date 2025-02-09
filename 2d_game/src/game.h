#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "camera.h"
#include "clock.h"
#include "map.h"
#include "monster.h"
#include "player.h"
#include "projectile.h"
#include "utils.h"

class Game
{
public:
	bool init(const char* title, int width, int height);
    bool online_init();
	void gameLoop();
    void OnlineGameLoop();
	void shutdown();
	SDL_Texture* loadTexture(const char* path);

protected:
	void handleEvent();
	void update();
	void draw();
    void projectile_collisions();
    void spawn_monster();

	bool isRunning{ true };

	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
	Clock* m_clock{ nullptr };
    Map* m_map{ nullptr };
    Camera m_camera{};

    Player* m_player{ nullptr };
    std::vector<Monster*> m_monsters{};
    std::vector<Projectile*> m_projectiles{};

    SDL_Texture* m_projectile_texture{ nullptr };
    SDL_Texture* m_monster_texture{ nullptr };

	bool isPaused{ false };
};

#endif // !GAME_H
