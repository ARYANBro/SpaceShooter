#include "Bullet.h"

#include "Scene.h"
#include "Game.h"

void Bullet::Update(float deltaTime) noexcept
{
	SetActiveFrameX((SDL_GetTicks() / 440) % 2);

	SDL_FRect& rect = GetRectangle();
	if (m_Fired)
	{
		rect.y += GetSpeedY() * deltaTime;	
		rect.x += GetSpeedX() * deltaTime;
	}

	if (rect.y <= 0 && !IsNull())
		Game::GetInstance().GetScene().DestroyEntity(this);
}

void Bullet::OnCollision(const Entity& entity)
{
	if (m_Parent.CheckTag("Enemy") && entity.CheckTag("Enemy"))
		return;
	
	if (!entity.CheckTag("Bullet") && &m_Parent != &entity)
	{
		SetCollided(true);
		Game::GetInstance().GetScene().DestroyEntity(this);
	}
}