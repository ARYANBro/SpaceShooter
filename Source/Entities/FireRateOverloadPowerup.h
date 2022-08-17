#pragma once

#include "PowerUp.h"
#include "Game.h"
#include "Globals.h"

class Player;

class FireRateOverloadPowerUp : public PowerUp
{
public:
	FireRateOverloadPowerUp(int scaleX = 1, int scaleY = 1) noexcept
		: PowerUp(Game::GetInstance().GetSpriteLoader().GetSprite(SpriteType::PowerUp), scaleX, scaleY)
	{
		GetSprite().SetFrameX(1);
		GetRectangle().y = Globals::Window::Height  - GetRectangle().h - 15;
		GetRectangle().x += GetRectangle().w + 15;
	}

	virtual void OnEquip(Player& player) noexcept override;
};