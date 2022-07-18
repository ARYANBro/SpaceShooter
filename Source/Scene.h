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

class Scene
{
public:
	Scene() noexcept;

	virtual ~Scene() noexcept;
	virtual void Update(float deltaTime) noexcept;
	virtual void Render() noexcept;
	virtual void ProcessEvents(SDL_Event& event) noexcept {}
	void DestroyEntity(Entity* entity) noexcept;
	virtual void Reset() noexcept;
	void SetUpdateEntities(bool value) noexcept { m_UpdateEntities = value; }
	void SetRenderEntities(bool value) noexcept { m_RenderEntities = value; }

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
	std::list<Entity*> m_Entities = { nullptr };
	std::list<Entity*> m_DelQueue = { nullptr };
	ScrollingBackGround m_BackGround;
	SpriteLoader m_SpriteLoader;
	SoundLoader m_SoundLoader;
	TextRenderer m_TextRenderer;

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
