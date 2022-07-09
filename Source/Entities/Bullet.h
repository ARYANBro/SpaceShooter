#pragma once

#include "PhysicsEntity.h"
#include "Sprite.h"

class Bullet : public PhysicsEntity
{
public:
	Bullet(Sprite& sprite, Entity& parent, int scaleX = 1, int scaleY = 1, Bullet* next = nullptr) noexcept
		: PhysicsEntity(sprite, scaleX, scaleY), m_Parent(parent), m_Next(nullptr)
	{
		AddTag("Bullet");
	}

	void Update(float deltaTime) noexcept;

	virtual void OnCollision(const Entity& entity) override;
	void Fire() noexcept { m_Fired = true; }
	void SetNext(Bullet* next) noexcept { m_Next = next; }
	bool IsFired() const noexcept { return m_Fired; }
	const Entity& GetParent() const noexcept { return m_Parent; }
	Bullet* GetNext() noexcept { return m_Next; }

private:
	bool m_Fired = false;
	Bullet* m_Next = nullptr;
	const Entity& m_Parent;
};