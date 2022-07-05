#pragma once

#include "PhysicsEntity.h"
#include "Sprite.h"

class Bullet : public PhysicsEntity
{
public:
	Bullet(Sprite& sprite, int scaleX = 1, int scaleY = 1) noexcept
		: PhysicsEntity(sprite, scaleX, scaleY)
	{
		AddTag("Bullet");
	}

	void Update(float deltaTime) noexcept;

	virtual void OnCollision(const Entity& entity) override;
	void Fire() noexcept { m_Fired = true; }
	bool IsFired() const noexcept { return m_Fired; }

private:
	bool m_Fired = false;
};