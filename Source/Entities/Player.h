#pragma once

#include "Entity.h"
#include "PhysicsEntity.h"
#include "Sprite.h"
#include "Timer.h"
#include "Scene.h"

#include <list>

class Player : public PhysicsEntity
{
public:
	Player(Sprite& sprite, int scaleX = 1, int scaleY = 1) noexcept;

	void Update() override;
	virtual void OnCollision(const Entity& entity) override;

private:
	Timer m_ReloadTimer{ 30 };
	Timer m_AnimationIdxL{ 20 };
	Timer m_AnimationIdxR{ 20 };

private:
	void ProcessInput() noexcept;
	void MoveLeft() noexcept;
	void MoveRight() noexcept;
	void MoveStraight() noexcept;
	void FireBullet() noexcept;
};