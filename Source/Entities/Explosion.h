#pragma once

#include "Entity.h"
#include "Timer.h"

class Sprite;

class Explosion : public Entity
{
public:
	Explosion(Sprite& sprite, int scaleX = 1, int scaleY = 1) noexcept;
	void Update(float deltaTime) override;

	const Timer& GetTimer() const noexcept { return m_Timer; }
	Timer& GetTimer() noexcept { return m_Timer; }

private:
	Timer m_Timer{ 0.38f };
	int m_AnimationIdx = -1;
};