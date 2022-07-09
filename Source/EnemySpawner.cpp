#include "EnemySpawner.h"

#include "Entities/Enemy.h"
#include "Entities/SmallEnemy.h"
#include "Entities/MediumEnemy.h"
#include "Entities/BigEnemy.h"
#include "Globals.h"
#include "Sprite.h"
#include "Scene.h"

#include <iostream>
#include <map>

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
		float rand = std::rand() / static_cast<float>(RAND_MAX);

		if (rand <= 0.6f)
			SpawnInitEnemy<SmallEnemy>();
		else if (rand <= 0.9f)
			SpawnInitEnemy<MediumEnemy>();
		else if (rand <= 1.0f)
			SpawnInitEnemy<BigEnemy>();

		float limit = m_MaxSpawnTime - m_MinSpawnTime;
		SetSpawnTimer(m_MinSpawnTime + (std::rand() / RAND_MAX) * limit);
	}
}
