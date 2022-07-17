#pragma once

#include <SDL2/SDL.h>

#include <cstdint>

class DeltaTime
{
public:
    void Update() noexcept
    {
	    m_Previous = m_Current;
        m_Current = SDL_GetTicks64();
	    m_DeltaTime = (m_Current - m_Previous) / 1000.0f;
    }

    std::uint64_t GetPrevious() const noexcept { return m_Previous; }
    double GetDeltaTime() const noexcept { return m_DeltaTime; }
    std::uint64_t GetCurrent() const noexcept { return m_Current; }

private:
    std::uint64_t m_Previous = 0;
    std::uint64_t m_Current = 0;
    double m_DeltaTime = 0;
};