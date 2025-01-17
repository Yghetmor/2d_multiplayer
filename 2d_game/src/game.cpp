#include "game.h"
#include "entity.h"
#include "utils.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>

bool Game::init(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL could not initialize. Error: " << SDL_GetError() << '\n';
		return false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			std::cout << "Warning: linear texture filtering not enabled.\n";
	}

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (m_window == nullptr)
	{
		std::cout << "Window could not be created. SDL Error: " << SDL_GetError() << '\n';
		return false;
	}
	else
	{
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (m_renderer == nullptr)
		{
			std::cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << '\n';
			return false;
		}
	}

	m_clock = new Clock;
    m_map = new Map(loadTexture("assets/map.png"));
    m_player = new Player(loadTexture("assets/player.png"));
    m_monsters.push_back(new Monster(100, 100, loadTexture("assets/monster.png")));

    m_projectile_texture = loadTexture("assets/projectile.png");

	return true;
}

void Game::gameLoop()
{
	while (isRunning)
	{
		if (!isPaused)
		{
			m_clock->tick();
			handleEvent();
			update();
			draw();
		}
		else
		{
			m_clock->tick();
			handleEvent();
		}
	}
}

void Game::shutdown()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = nullptr;
	m_window = nullptr;

	delete m_clock;
	m_clock = nullptr;

    delete m_map;
    m_map = nullptr;

    delete m_player;
    m_player = nullptr;

    for (auto monster : m_monsters)
    {
        if (monster != nullptr)
        {
            delete monster;
            monster = nullptr;
        }
    }

    for (auto projectile : m_projectiles)
    {
        if (projectile != nullptr)
        {
            delete projectile;
            projectile = nullptr;
        }
    }

    SDL_DestroyTexture(m_projectile_texture);

	SDL_Quit();
}

SDL_Texture* Game::loadTexture(const char* path)
{
	SDL_Texture* texture{ nullptr };

	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == nullptr)
		std::cout << "Unable to load image " << path << "! SDL_Image Error:" << IMG_GetError() << '\n';
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (texture == nullptr)
			std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << '\n';

		SDL_FreeSurface(loadedSurface);
	}

	return texture;
}

void Game::handleEvent()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
        {
			isRunning = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            m_projectiles.push_back(new Projectile(m_player, m_projectile_texture));
        }

        m_player->handle_event(event);
	}
}

void Game::update()
{
    m_player->update_position(&m_camera);
    m_camera.update(m_player->get_x(), m_player->get_y(), m_player->get_width(), m_player->get_height());

    for (auto& monster : m_monsters)
    {
        if (monster != nullptr)
            monster->update_position(m_player);
    }

    for (auto& projectile : m_projectiles)
    {
        if (projectile != nullptr)
        {
            projectile->update_position();
            if (!projectile->is_alive())
            {
                delete projectile;
                projectile = nullptr;
            }
        }
    }
}

void Game::draw()
{
	SDL_SetRenderDrawColor(m_renderer, 40, 40, 40, 0xFF);
	SDL_RenderClear(m_renderer);

    m_map->render(m_renderer, &m_camera);

    m_player->render(m_renderer, &m_camera);

    for (auto monster : m_monsters)
    {
        if (monster != nullptr)
            monster->render(m_renderer, &m_camera);
    }

    for (auto projectile : m_projectiles)
    {
        if (projectile != nullptr)
            projectile->render(m_renderer, &m_camera);
    }

	SDL_RenderPresent(m_renderer);
}
