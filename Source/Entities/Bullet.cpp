#include "Bullet.h"

#include "Scene.h"

void Bullet::Update() noexcept
{
	SetActiveFrameX((SDL_GetTicks() / 440) % 2);

	SDL_FRect& rect = GetRectangle();
	if (m_Fired)
	{
		rect.y += GetSpeedY();	
		rect.x += GetSpeedX();
	}

	if (rect.y <= 0 || Collided() && !IsNull())
		Scene::GetInstance().DestroyEntity(this);
}

void Bullet::OnCollision(const Entity& entity)
{
	if (!entity.CheckTag("Bullet"))
		SetCollided(true);
}