#include "PowerUp.h"

#include "Player.h"

void PowerUp::OnCollision(Entity& entity) noexcept
{
	if (entity.CheckTag("Player"))
	{
		OnEquip(static_cast<Player&>(entity));
		Hide();
	}
}
