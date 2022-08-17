#pragma once

#include "PhysicsEntity.h"
#include "Sprite.h"

class Bullet : public PhysicsEntity
{
public:
	Bullet(Sprite& sprite, Entity& parent, int damage = 1, int scaleX = 1, int scaleY = 1, Bullet* next = nullptr) noexcept
		: PhysicsEntity(sprite, scaleX, scaleY), m_Parent(parent), m_Damage(damage), m_Next(nullptr)
	{
		AddTag("Bullet");
	}

	void Update(float deltaTime) noexcept;

	virtual void OnCollision( Entity& entity) override;
	int GetDamage() const noexcept { return m_Damage; }
	void Fire() noexcept { m_Fired = true; }
	void SetNext(Bullet* next) noexcept { m_Next = next; }
	bool IsFired() const noexcept { return m_Fired; }
	const Entity& GetParent() const noexcept { return m_Parent; }
	Bullet* GetNext() noexcept { return m_Next; }

private:
	bool m_Fired = false;
	Bullet* m_Next = nullptr;
	const Entity& m_Parent;
	int m_Damage;
};