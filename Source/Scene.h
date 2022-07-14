#pragma once

#include "Entities/Entity.h"
#include "Sprite.h"
#include "Globals.h"
#include "Timer.h"
#include "BackGround.h"
#include "SoundLoader.h"
#include "SpriteLoader.h"
#include "DeltaTime.h"
#include "FontRenderer.h"

#include <list>
#include <SDL2/SDL_ttf.h>

class EnemySpawner;

class Scene
{
public:
	Scene() noexcept;

	~Scene() noexcept;
	void Update() noexcept;
	void Render() noexcept;
	void DestroyEntity(Entity* entity) noexcept;
	void Reset() noexcept;
	void ResetScore() noexcept { m_Score = 0; }
	void IncreaseScore() noexcept { m_Score++; }

	template<typename EntityType, typename... Args> requires std::is_base_of_v<Entity, EntityType>
	EntityType& CreateEntity(Args&&... args) noexcept;

	std::list<Entity*>& GetEntities() noexcept { return m_Entities; }
	const std::list<Entity*>& GetEntities() const noexcept { return m_Entities; }
	SpriteLoader& GetSpriteLoader() noexcept { return m_SpriteLoader; }
	SoundLoader& GetSoundLoader() noexcept { return m_SoundLoader; } 
	static Scene& GetInstance() noexcept { return *s_Scene; }
	bool GetGameOver() const noexcept { return m_GameOver; }

private:
	bool m_GameOver = false;
	DeltaTime m_DeltaTime;
	Timer m_ResetTimer{ 2.0f };
	std::list<Entity*> m_Entities;
	std::list<Entity*> m_DelQueue;
	ScrollingBackGround m_BackGround;
	SpriteLoader m_SpriteLoader;
	SoundLoader m_SoundLoader;
	FontRenderer m_FontRenderer;
	EnemySpawner* m_Spawner;
	std::uint_least64_t m_Score = 0;
	std::uint_least64_t m_HighScore = 0;

	static Scene* s_Scene;

private:
	void SetGameOver(bool gameOver) noexcept { m_GameOver = gameOver; }

	void LoadSprites() noexcept;
	void LoadSounds() noexcept;
	void LoadScene() noexcept;
	void PhysicsUpdate() noexcept;
	void DeleteQueue() noexcept;
};

template<typename EntityType, typename... Args> requires std::is_base_of_v<Entity, EntityType>
EntityType& Scene::CreateEntity(Args&&... args) noexcept
{
	EntityType* entity = new EntityType(std::forward<Args>(args)...);
	m_Entities.push_back(entity);
	return *entity;
}
