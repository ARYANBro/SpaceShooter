#include "Entity.h"

#include "Scene.h"
#include "Sprite.h"

Entity::Entity(Sprite& sprite, int scaleX, int scaleY) noexcept
	: m_Sprite(sprite)
{
	m_Rect.w = m_Sprite.GetFrameWidth() * scaleX;
	m_Rect.h = m_Sprite.GetFrameHeight() * scaleY;

	AddTag("Entity");
}

bool Entity::CheckTag(const std::string& tag) const noexcept
{
	const std::string* found = std::find(m_Tags.begin(), m_Tags.end(), tag);
	return found != m_Tags.end() ? true : false;
}