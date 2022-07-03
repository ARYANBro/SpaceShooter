#pragma once

#include <list>

#include "Timer.h"

class Sprite;
class Scene;

class EnemySpawner
{
public:
	EnemySpawner(int spawnTimer) noexcept
		: m_SpawnTimer(spawnTimer) {}

	void SetSpawnTimer(int time) noexcept;
	void Spawn(Sprite& sprite, int x, int y) noexcept;
	void Update() noexcept;

private:
	Timer m_SpawnTimer;

private:
	void UpdateTimer() noexcept;
};