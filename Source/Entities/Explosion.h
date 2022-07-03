#pragma once

#include "Entity.h"
#include "Timer.h"

class Sprite;

class Explosion : public Entity
{
public:
	Explosion(Sprite& sprite, int scaleX = 1, int scaleY = 1) noexcept;
	void Update() override;

private:
	Timer m_Timer{ 30 };
	int m_AnimationIdx = -1;
};