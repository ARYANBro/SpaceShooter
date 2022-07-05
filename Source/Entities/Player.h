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

	void Update(float deltaTime) override;
	virtual void OnCollision(const Entity& entity) override;

private:
	Timer m_ReloadTimer{ 0.5 };
	Timer m_AnimationIdxL{ 0.3f };
	Timer m_AnimationIdxR{ 0.3f };

private:
	void ProcessInput(float deltaTime) noexcept;
	void MoveLeft(float deltaTime) noexcept;
	void MoveRight(float deltaTime) noexcept;
	void MoveStraight() noexcept;
	void FireBullet() noexcept;
};