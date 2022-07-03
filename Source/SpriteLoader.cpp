#include "SpriteLoader.h"


void SpriteLoader::Load(SpriteType type, const std::string& path, const std::pair<int, int>& frames) noexcept
{
	m_Sprites[static_cast<int>(type)].Load(path, frames.first, frames.second);
}