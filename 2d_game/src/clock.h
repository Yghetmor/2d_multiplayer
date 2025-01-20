#ifndef CLOCK_H
#define CLOCK_H

#include <SDL2/SDL.h>

class Clock
{
public:

    Clock();

    void start();
    void stop();
    void pause();
    void unpause();
    void reset();

    int get_ticks();

    bool is_started();
    bool is_paused();

private:
	int m_start_ticks{};
	int m_paused_ticks{};

    bool m_paused{};
    bool m_started{};
};

#endif // !CLOCK_H
