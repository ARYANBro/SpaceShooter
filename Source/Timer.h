#pragma once

class Timer
{
public:	
	Timer(float time = 0) noexcept
		: m_TargetTime(time) {}

	void Update(float deltaTime) noexcept;
	void Reset() noexcept;

	void SetTime(float time) noexcept { m_TargetTime = time; }
	bool IsExpired() const noexcept { return m_Expired; }
	float GetCurrentTime() const noexcept { return m_CurrentTime; }
	float GetTargetTime() const noexcept { return m_TargetTime; }

private:
	float m_TargetTime = 0;
	float m_CurrentTime = 0;
	bool m_Expired = false;
};