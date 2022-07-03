#pragma once

class Timer
{
public:	
	Timer(int time = 0) noexcept
		: m_TargetTime(time) {}

	void Update() noexcept;
	void Reset() noexcept;

	void SetTime(int time) noexcept { m_TargetTime = time; }
	bool IsExpired() const noexcept { return m_Expired; }
	int GetCurrentTime() const noexcept { return m_CurrentTime; }

private:
	int m_TargetTime = 0;
	int m_CurrentTime = 0;
	bool m_Expired = false;
};