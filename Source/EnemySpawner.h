#pragma once

#include "Timer.h"

class Sprite;

class EnemySpawner
{
public:
	EnemySpawner(float minSpawnTime, float maxSpawnTime) noexcept;

	void SetSpawnTimer(float time) noexcept;

	template<typename EnemyType>
	EnemyType& Spawn(Sprite& sprite, int x, int y) noexcept;

	void Update(float deltaTime) noexcept;

	void SetSpawnChance(float smallEnemy, float mediumEnemy, float bigEnemy) noexcept
	{
		m_SmallESpawnChance = smallEnemy;
		m_MediumESpawnChance = mediumEnemy;
		m_BigESpawnChance = bigEnemy;
	}

private:
	float m_MinSpawnTime, m_MaxSpawnTime;
	float m_SmallESpawnChance = 0.6f, m_MediumESpawnChance = 0.9f, m_BigESpawnChance = 1.0f;
	Timer m_SpawnTimer;

private:
	void UpdateTimer(float deltaTime) noexcept;

	template<typename EnemyType>
	EnemyType& SpawnInitEnemy() noexcept;
};

#include "EnemySpawner.inl"