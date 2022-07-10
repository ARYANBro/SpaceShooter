#pragma once

#include <SDL2/SDL.h>

class DeltaTime
{
public:
    void Update() noexcept
    {
        double current = SDL_GetTicks() / 1000.0f;
	    m_DeltaTime = current - m_Previous;
	    m_Previous = current;
    }

    float GetPrevious() const noexcept { return m_Previous; }
    float GetDeltaTime() const noexcept { return m_DeltaTime; }

private:
    float m_Previous = 0;
    float m_DeltaTime = 0;
};