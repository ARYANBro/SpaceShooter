#include "EnemySpawner.h"

#include "Scene.h"
#include "Entities/SmallEnemy.h"
#include "Entities/MediumEnemy.h"
#include "Entities/BigEnemy.h"

template<typename EnemyType>
EnemyType& EnemySpawner::Spawn(Sprite& sprite, int x, int y) noexcept
{
	EnemyType& enemy = Scene::GetInstance().CreateEntity<EnemyType>(sprite, 2.0f, 2.0f);
	enemy.GetRectangle().x = x;
	enemy.GetRectangle().y = y;
	enemy.SetSpeedX(30.0f + (std::rand() / static_cast<float>(RAND_MAX)) * 20.0f);
	enemy.SetSpeedY(30.0f + (std::rand() / static_cast<float>(RAND_MAX)) * 60.0f);
	return enemy;
}

template<typename EnemyType>
EnemyType& EnemySpawner::SpawnInitEnemy() noexcept
{
	SpriteType spriteType;
	if (std::is_same_v<EnemyType, SmallEnemy>)
		spriteType = SpriteType::SmallEnemy;
	else if (std::is_same_v<EnemyType, MediumEnemy>)
		spriteType = SpriteType::MediumEnemy;
	else if (std::is_same_v<EnemyType, BigEnemy>)
		spriteType = SpriteType::BigEnemy;

	Sprite& sprite = Scene::GetInstance().GetSpriteLoader().GetSprite(spriteType);
	int x = (std::rand() / static_cast<float>(RAND_MAX)) * (Globals::Window::Width - sprite.GetFrameWidth());
	int y = sprite.GetFrameHeight() * -2;
	return Spawn<EnemyType>(sprite, x, y);
}