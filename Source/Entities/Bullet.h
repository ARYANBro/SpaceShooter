#pragma once

#include "PhysicsEntity.h"
#include "Sprite.h"

class Bullet : public PhysicsEntity
{
public:
	Bullet(Sprite& sprite, Entity& parent, int scaleX = 1, int scaleY = 1) noexcept
		: PhysicsEntity(sprite, scaleX, scaleY), m_Parent(parent)
	{
		AddTag("Bullet");
	}

	void Update(float deltaTime) noexcept;

	virtual void OnCollision(const Entity& entity) override;
	void Fire() noexcept { m_Fired = true; }
	bool IsFired() const noexcept { return m_Fired; }
	const Entity& GetParent() const noexcept { return m_Parent; }

private:
	bool m_Fired = false;
	const Entity& m_Parent;
};