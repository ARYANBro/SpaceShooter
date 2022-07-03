#pragma once

#include "PhysicsEntity.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Timer.h"

class Scene;

class Enemy : public PhysicsEntity
{
public:
	Enemy(Sprite& sprite, int scaleX = 1, int scaleY = 1) noexcept
		: PhysicsEntity(sprite, scaleX, scaleY)
	{
		AddTag("Enemy");	
	}
		
	virtual void Update() override;
	virtual void OnCollision(const Entity& entity) override;
private:
	friend class Scene;

private:
	Timer m_ReloadTimer{ 140 };
	
private:
	void FireBullet() noexcept;
	std::pair<float, float> CalculateBulletDir(const Bullet& bullet, float speedMultiplier) noexcept;
};