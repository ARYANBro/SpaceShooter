#pragma once

#include "PhysicsEntity.h"

class Player;

class PowerUp : public PhysicsEntity
{
public:
	PowerUp(Sprite& sprite, int scaleX = 1, int scaleY = 1) noexcept
		: PhysicsEntity(sprite, scaleX, scaleY) { AddTag("PowerUp"); }

	virtual void OnCollision(Entity& entity) noexcept override;

	virtual ~PowerUp() noexcept = default;
	virtual void OnEquip(Player& player) noexcept = 0;
};	