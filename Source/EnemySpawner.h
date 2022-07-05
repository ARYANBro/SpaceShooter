#pragma once

#include <list>

#include "Timer.h"

class Sprite;
class Scene;

class EnemySpawner
{
public:
	EnemySpawner(float minSpawnTime, float maxSpawnTime) noexcept;

	void SetSpawnTimer(float time) noexcept;
	void Spawn(Sprite& sprite, int x, int y) noexcept;
	void Update(float deltaTime) noexcept;

private:
	float m_MinSpawnTime, m_MaxSpawnTime;
	Timer m_SpawnTimer;

private:
	void UpdateTimer(float deltaTime) noexcept;
};