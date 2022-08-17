#pragma once

#include "PowerUp.h"
#include "Game.h"
#include "Globals.h"

class KillShotPowerUp : public PowerUp
{
public:
	KillShotPowerUp(int scaleX = 1, int scaleY = 1)
		: PowerUp(Game::GetInstance().GetSpriteLoader().GetSprite(SpriteType::PowerUp), scaleX, scaleY)
	{
		GetRectangle().y = Globals::Window::Height  - GetRectangle().h - 15;
	}

	virtual void OnEquip(Player& player) noexcept override;
};