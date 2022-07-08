#pragma once

#include "Sprite.h"

#include <array>

enum class SpriteType
{
	Explosion, Player, Bullet, SmallEnemy, MediumEnemy, BigEnemy
};

class SpriteLoader
{
public:
	void Load(SpriteType type, const std::string& path, const std::pair<int, int>& frames) noexcept;
	const Sprite& GetSprite(SpriteType type) const noexcept { return m_Sprites[static_cast<int>(type)]; }
	Sprite& GetSprite(SpriteType type) noexcept { return m_Sprites[static_cast<int>(type)]; }

private:
	std::array<Sprite, 6> m_Sprites;
};