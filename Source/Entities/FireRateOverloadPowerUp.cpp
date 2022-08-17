#include "FireRateOverloadPowerup.h"

#include "Player.h"

void FireRateOverloadPowerUp::OnEquip(Player& player) noexcept
{
	player.SetReloadTimer(0.2);
}

