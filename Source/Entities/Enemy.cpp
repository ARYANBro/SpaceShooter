#include "Enemy.h"

#include "Scene.h"
#include "Bullet.h"
#include "Player.h"
#include "Globals.h"
#include "Explosion.h"

#include <SDL2/SDL_mixer.h>

#include <cassert>
#include <cmath>

static void CalculateSlope(SDL_FRect rect1, SDL_FRect rect2, SDL_FRect& inRect) noexcept
{
	float distance = std::max(std::abs(rect1.y - rect2.y), std::abs(rect1.x - rect2.x));

	inRect.x = (rect1.x - rect2.x) / distance;
	inRect.y = (rect1.y - rect2.y) / distance;
}

void Enemy::Update(float deltaTime)
{
	GetRectangle().y += GetSpeedX() * deltaTime;

	m_ReloadTimer.Update(deltaTime);
	if (m_ReloadTimer.IsExpired())
	{
		m_ReloadTimer.Reset();
		FireBullet();
	}
}

void Enemy::OnCollision(const Entity& entity)
{
	PhysicsEntity::OnCollision(entity);
	Explosion& explosion = Scene::GetInstance().CreateEntity<Explosion>(Scene::GetInstance().GetSpriteLoader().GetSprite(SpriteType::Explosion), 3, 3);
	explosion.GetRectangle().x = GetRectangle().x;
	explosion.GetRectangle().y = GetRectangle().y;
}

void Enemy::FireBullet() noexcept
{
	Bullet& bullet = Scene::GetInstance().CreateEntity<Bullet>(
		Scene::GetInstance().GetSpriteLoader().GetSprite(SpriteType::Bullet),
		2, 2
	);

	bullet.Fire();
	bullet.GetRectangle().x = GetRectangle().x;
	bullet.GetRectangle().y = GetRectangle().y + bullet.GetRectangle().h;
	
	auto [speedX, speedY] = CalculateBulletDir(bullet, 250.0f);
	bullet.SetSpeedX(speedX);
	bullet.SetSpeedY(speedY);

	Scene::GetInstance().GetSoundLoader().PlaySound(SoundFXType::EnemyFire);
}

std::pair<float, float> Enemy::CalculateBulletDir(const Bullet& bullet, float speedMultiplier) noexcept
{
	SDL_FRect inRect;
	for (Entity* entity : Scene::GetInstance().GetEntities())
	{
		if (entity->CheckTag("Player"))
		{
			SDL_FRect r1;
			r1.x = entity->GetRectangle().x + entity->GetRectangle().w / 2.0f;
			r1.y = entity->GetRectangle().y + entity->GetRectangle().h / 2.0f;
			
			CalculateSlope(r1, GetRectangle(), inRect);
			break;
		}
	}

	return { inRect.x * speedMultiplier, inRect.y * speedMultiplier };
}