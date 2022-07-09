#pragma once

#include "PhysicsEntity.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Timer.h"

class Scene;

class Enemy : public PhysicsEntity
{
public:
	Enemy(Sprite& sprite, int scaleX = 1, int scaleY = 1, int lives = 1) noexcept
		: PhysicsEntity(sprite, scaleX, scaleY), m_Lives(lives)
	{
		AddTag("Enemy");	
	}

	virtual void Update(float deltaTime) override;
	virtual void OnCollision(const Entity& entity) override;

	virtual Bullet* FireBullet() noexcept;

private:
	friend class Scene;

private:
	Timer m_ReloadTimer{ 2.0f };
	int m_Lives;
	
private:
	std::pair<float, float> CalculateBulletDir(const Bullet& bullet, float speedMultiplier) noexcept;
};