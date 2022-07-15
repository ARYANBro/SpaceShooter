#pragma once

#include "Entities/Entity.h"
#include "BackGround.h"
#include "SoundLoader.h"
#include "SpriteLoader.h"
#include "DeltaTime.h"
#include "FontRenderer.h"
#include "HighScore.h"

#include <list>
#include <SDL2/SDL_ttf.h>

class EnemySpawner;

class Scene
{
public:
	Scene() noexcept;

	~Scene() noexcept;
	virtual DeltaTime Update() noexcept;
	virtual void Render() noexcept;
	void DestroyEntity(Entity* entity) noexcept;
	virtual void Reset() noexcept;
	void ResetScore() noexcept { m_Score = 0; }
	void SetUpdateEntities(bool value) noexcept { m_UpdateEntities = value; }
	void SetRenderEntities(bool value) noexcept { m_RenderEntities = value; }
	void IncreaseScore() noexcept;

	template<typename EntityType, typename... Args> requires std::is_base_of_v<Entity, EntityType>
	EntityType& CreateEntity(Args&&... args) noexcept;

	std::list<Entity*>& GetEntities() noexcept { return m_Entities; }
	const std::list<Entity*>& GetEntities() const noexcept { return m_Entities; }
	SpriteLoader& GetSpriteLoader() noexcept { return m_SpriteLoader; }
	SoundLoader& GetSoundLoader() noexcept { return m_SoundLoader; } 
	TextRenderer& GetTextRenderer() noexcept { return m_TextRenderer; }
	static Scene& GetInstance() noexcept { return *s_Scene; }

private:
	bool m_UpdateEntities = true, m_RenderEntities = true;
	DeltaTime m_DeltaTime;
	std::list<Entity*> m_Entities;
	std::list<Entity*> m_DelQueue;
	ScrollingBackGround m_BackGround;
	SpriteLoader m_SpriteLoader;
	SoundLoader m_SoundLoader;
	TextRenderer m_TextRenderer;
	HighScoreTable m_HighScoreTable;
	std::uint_least64_t m_Score = 0;

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
