#include "Bullet.h"

#include "Scene.h"

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
		Scene::GetInstance().DestroyEntity(this);
}

void Bullet::OnCollision(const Entity& entity)
{
	if (!entity.CheckTag("Bullet"))
	{
		SetCollided(true);
		Scene::GetInstance().DestroyEntity(this);
	}
}