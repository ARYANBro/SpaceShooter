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
	Player(Sprite& sprite, int scaleX = 1, int scaleY = 1, const std::string& name = "Anonymous") noexcept;

	void Update(float deltaTime) override;
	virtual void OnCollision(Entity& entity) override;
	void SetDamage(int damage) noexcept { m_Damage = damage; }
	void SetReloadTimer(float time) noexcept { m_ReloadTimer.SetTime(time); }
	void SetName(const std::string& name) noexcept { m_Name = name; }
	const std::string& GetName() const noexcept { return m_Name; }
	std::string& GetName() noexcept { return m_Name; }

private:
	Timer m_ReloadTimer{ 0.5 };
	Timer m_AnimationIdxL{ 0.2f };
	Timer m_AnimationIdxR{ 0.2f };
	Timer m_DeathTimer;
	std::string m_Name;
	int m_Damage = 1;

private:
	void ProcessInput(float deltaTime) noexcept;
	void MoveLeft(float deltaTime) noexcept;
	void MoveRight(float deltaTime) noexcept;
	void MoveStraight() noexcept;
	void FireBullet() noexcept;
};