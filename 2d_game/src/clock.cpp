#include "clock.h"

Clock::Clock()
 : m_start_ticks{0}, m_paused_ticks{0}, m_paused{false}, m_started{false} {}

void Clock::start()
{
    m_started = true;
    m_paused = false;

    m_start_ticks = SDL_GetTicks();
    m_paused_ticks = 0;
}

void Clock::stop()
{
    m_started = false;
    m_paused = false;

    m_start_ticks = 0;
    m_paused_ticks = 0;
}

void Clock::pause()
{
    if (m_started && !m_paused)
    {
        m_paused = true;

        m_paused_ticks = SDL_GetTicks() - m_start_ticks;
        m_start_ticks = 0;
    }
}

void Clock::unpause()
{
    if (m_started && m_paused)
    {
        m_paused = false;

        m_start_ticks = SDL_GetTicks() - m_paused_ticks;
        m_paused_ticks = 0;
    }
}

void Clock::reset()
{
    if (m_started)
    {
        m_start_ticks = SDL_GetTicks();
        m_paused_ticks = 0;
        m_paused = false;
    }
}

int Clock::get_ticks()
{
    int time = 0;

    if (m_started)
    {
        if (m_paused)
        {
            time = m_paused_ticks;
        }
        else
        {
            time = SDL_GetTicks() - m_start_ticks;
        }
    }

    return time;
}

bool Clock::is_paused()
{
    return m_paused;
}

bool Clock::is_started()
{
    return m_started;
}
