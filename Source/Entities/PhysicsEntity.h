#pragma once

#include "Entity.h"

class Scene;
class Sprite;

class PhysicsEntity : public Entity
{
public:
	PhysicsEntity(Sprite& sprite, int scaleX, int scaleY) noexcept
		: Entity(sprite, scaleX, scaleY)
	{
		AddTag("PhysicsEntity");
	}

	virtual void OnCollision(Entity& entity) { m_Collided = true; };

	bool Collided() const noexcept { return m_Collided; }

protected:
	void SetCollided(bool collided) noexcept { m_Collided = collided; }

private:
	bool m_Collided = false;
};