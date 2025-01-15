#ifndef CLOCK_H
#define CLOCK_H

#include <SDL2/SDL.h>

class Clock
{
public:
	void tick()
	{
		int tickTime = SDL_GetTicks();
		m_delta = tickTime - m_lastTickTime;
		m_lastTickTime = tickTime;
	}

	int getDelta() const { return m_delta; }

private:
	int m_lastTickTime{};
	int m_delta{};
};

#endif // !CLOCK_H
