#pragma once

#include "Entities/Entity.h"
#include "Sprite.h"
#include "Globals.h"
#include "Timer.h"
#include "BackGround.h"
#include "EnemySpawner.h"
#include "SpriteLoader.h"
#include "SoundLoader.h"

#include <SDL2/SDL_mixer.h>

#include <list>
#include <map>
#include <concepts>
#include <array>
#include <vector>

class Scene
{
public:
	Scene() noexcept;

	~Scene() noexcept;
	void Update() noexcept;
	void Render() noexcept;
	void DestroyEntity(Entity* entity) noexcept;
	void Reset() noexcept;

	template<typename EntityType, typename... Args> requires std::is_base_of_v<Entity, EntityType>
	EntityType& CreateEntity(Args&&... args) noexcept;

	std::list<Entity*>& GetEntities() noexcept { return m_Entities; }
	const std::list<Entity*>& GetEntities() const noexcept { return m_Entities; }
	SpriteLoader& GetSpriteLoader() noexcept { return m_SpriteLoader; }
	SoundLoader& GetSoundLoader() noexcept { return m_SoundLoader; } 
	static Scene& GetInstance() noexcept { return *s_Scene; }

private:
	bool m_GameOver = false;
	double m_Previous = 0.0;
	Timer m_ResetTimer{ 2.0f };
	std::list<Entity*> m_Entities;
	std::list<Entity*> m_DelQueue;
	ScrollingBackGround m_BackGround;
	SoundLoader m_SoundLoader;
	SpriteLoader m_SpriteLoader;
	EnemySpawner m_Spawner;

	static Scene* s_Scene;

private:
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
