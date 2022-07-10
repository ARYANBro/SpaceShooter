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
}

void EnemySpawner::UpdateTimer(float deltaTime) noexcept
{
	m_SpawnTimer.Update(deltaTime);

	if (m_SpawnTimer.IsExpired())
	{
		float rand = std::rand() / static_cast<float>(RAND_MAX);

		if (rand <= m_SmallESpawnChance)
			SpawnInitEnemy<SmallEnemy>();
		else if (rand <= m_MediumESpawnChance)
			SpawnInitEnemy<MediumEnemy>();
		else if (rand <= m_BigESpawnChance)
			SpawnInitEnemy<BigEnemy>();

		float limit = m_MaxSpawnTime - m_MinSpawnTime;
		SetSpawnTimer(m_MinSpawnTime + (std::rand() / RAND_MAX) * limit);
	}
}
