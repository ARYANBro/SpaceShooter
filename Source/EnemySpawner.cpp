#include "EnemySpawner.h"

#include "Entities/Enemy.h"
#include "Globals.h"
#include "Sprite.h"
#include "Scene.h"

#include <cassert>

EnemySpawner::EnemySpawner(float minSpawnTime, float maxSpawnTime) noexcept
	: m_MinSpawnTime(minSpawnTime), m_MaxSpawnTime(maxSpawnTime)
{
	float limit = maxSpawnTime - minSpawnTime;
	SetSpawnTimer(minSpawnTime + (std::rand() / RAND_MAX) * limit);
}

void EnemySpawner::SetSpawnTimer(float time) noexcept
{
	m_SpawnTimer.Reset();
	m_SpawnTimer.SetTime(time);
}

void EnemySpawner::Spawn(Sprite& sprite, int x, int y) noexcept
{
	Enemy& enemy = Scene::GetInstance().CreateEntity<Enemy>(sprite, 2.0f, 2.0f);
	enemy.GetRectangle().x = x;
	enemy.GetRectangle().y = y;
	enemy.SetSpeedX(30.0f + (std::rand() / static_cast<float>(RAND_MAX)) * 60.0f);
}

void EnemySpawner::Update(float deltaTime) noexcept
{
	UpdateTimer(deltaTime);

	std::list<Entity*>::iterator it = Scene::GetInstance().GetEntities().begin();
	while (it != Scene::GetInstance().GetEntities().end())
	{
		Entity* enemy = *it++;
		if (enemy->CheckTag("Enemy"))
		{
			if (enemy->GetRectangle().y >= Globals::Window::Height || static_cast<Enemy*>(enemy)->Collided())
				Scene::GetInstance().DestroyEntity(enemy);
		}
	}
}

void EnemySpawner::UpdateTimer(float deltaTime) noexcept
{
	m_SpawnTimer.Update(deltaTime);

	if (m_SpawnTimer.IsExpired())
	{
		Sprite& sprite = Scene::GetInstance().GetSpriteLoader().GetSprite(SpriteType::Enemy);
		int x = (std::rand() / static_cast<float>(RAND_MAX)) * (Globals::Window::Width - sprite.GetFrameWidth());
		int y = sprite.GetFrameHeight() * -2;
		Spawn(sprite, x, y);

		float limit = m_MaxSpawnTime - m_MinSpawnTime;
		SetSpawnTimer(m_MinSpawnTime + (std::rand() / RAND_MAX) * limit);
	}
}
