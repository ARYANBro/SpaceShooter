#include "Timer.h"

void Timer::Update(float deltaTime) noexcept
{
	m_CurrentTime += deltaTime;
	if (m_CurrentTime >= m_TargetTime)
		m_Expired = true;
}

void Timer::Reset() noexcept
{
	m_Expired = false;
	m_CurrentTime = 0.0f;
}