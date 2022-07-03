#include "Timer.h"

void Timer::Update() noexcept
{
	if (++m_CurrentTime >= m_TargetTime)
			m_Expired = true;
}

void Timer::Reset() noexcept
{
	m_Expired = false;
	m_CurrentTime = 0;
}