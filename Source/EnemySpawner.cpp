#include "EnemySpawner.h"

#include "Entities/Enemy.h"
#include "Globals.h"
#include "Sprite.h"
#include "Scene.h"

#include <cassert>

void EnemySpawner::SetSpawnTimer(int time) noexcept
{
	m_SpawnTimer.Reset();
	m_SpawnTimer.SetTime(time);
}

void EnemySpawner::Spawn(Sprite& sprite, int x, int y) noexcept
{
	Enemy& enemy = Scene::GetInstance().CreateEntity<Enemy>(sprite, 2.0f, 2.0f);
	enemy.GetRectangle().x = x;
	enemy.GetRectangle().y = y;
	enemy.SetSpeedX(0.1 + (std::rand() / static_cast<float>(RAND_MAX)) * 0.9f);
}

void EnemySpawner::Update() noexcept
{
	UpdateTimer();

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

void EnemySpawner::UpdateTimer() noexcept
{
	m_SpawnTimer.Update();

	if (m_SpawnTimer.IsExpired())
	{
		Sprite& sprite = Scene::GetInstance().GetSpriteLoader().GetSprite(SpriteType::Enemy);
		int x = (std::rand() / static_cast<float>(RAND_MAX)) * (Globals::Window::Width - sprite.GetFrameWidth());
		int y = sprite.GetFrameHeight() * -2;
		Spawn(sprite, x, y);
		SetSpawnTimer(60 + (std::rand() % 59));		
	}
}
