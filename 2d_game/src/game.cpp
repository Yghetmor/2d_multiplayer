#include "game.h"
#include "entity.h"
#include "utils.h"

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
			isRunning = false;

        m_player->handle_event(event);
	}
}

void Game::update()
{
    m_player->update_position(&m_camera);
    m_camera.update(m_player->get_x(), m_player->get_y(), m_player->get_width(), m_player->get_height());
}

void Game::draw()
{
	SDL_SetRenderDrawColor(m_renderer, 40, 40, 40, 0xFF);
	SDL_RenderClear(m_renderer);

    m_map->render(m_renderer, &m_camera);

    m_player->render(m_renderer, &m_camera);

	SDL_RenderPresent(m_renderer);
}
