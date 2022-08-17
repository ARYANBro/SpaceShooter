#include "KillShotPowerUp.h"

#include "Player.h"

void KillShotPowerUp::OnEquip(Player& player) noexcept 
{
	player.SetDamage(3);
}