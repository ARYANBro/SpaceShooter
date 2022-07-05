#include "Scene.h"

#include "Sprite.h"
#include "Entities/Player.h"
#include "Entities/Enemy.h"
#include "Entities/Bullet.h"
#include "Entities/PhysicsEntity.h"
#include "Entities/Explosion.h"

#include <cassert>
#include <iostream>

static void RenderTexture(SDL_Texture* texture, SDL_Rect& texRect, const SDL_FRect& rectangle) noexcept
{
	SDL_RenderCopyF(Globals::Renderer::Renderer, texture, &texRect, &rectangle);
}

static void RenderSprite(Sprite& sprite, const SDL_FRect& rect) noexcept
{
	RenderTexture(sprite.GetTexture(), sprite.GetRectangle(), rect);
}

static void Render(Entity& entity) noexcept
{
	entity.GetSprite().SetFrameX(entity.GetActiveFrameX());
	entity.GetSprite().SetFrameY(entity.GetActiveFrameY());
	RenderSprite(entity.GetSprite(), entity.GetRectangle());
}

static bool CheckCollision(SDL_FRect rect1, SDL_FRect rect2) noexcept
{
	return std::max(rect1.x, rect2.x) < std::min(rect1.x + rect1.w, rect2.x + rect2.w) && std::max(rect1.y, rect2.y) < std::min(rect1.y + rect1.h, rect2.y + rect2.h);
}

Scene* Scene::s_Scene = nullptr;

Scene::Scene() noexcept
	: m_Spawner(2.0f, 3.0f)
{
	s_Scene = this;
	LoadSprites();
	LoadSounds();
	LoadScene();
}

Scene::~Scene() noexcept
{
	for (Entity* entity : m_Entities)
		delete entity;
}

void Scene::Update() noexcept
{
	double current = SDL_GetTicks() / 1000.0f;
	double deltaTime = current - m_Previous;
	m_Previous = current;

	m_BackGround.Update(deltaTime);

	if (!m_GameOver)
	{
		m_Spawner.Update(deltaTime);
		PhysicsUpdate();

		for (Entity* entity : m_Entities)
			entity->Update(deltaTime);
	}
	else
	{
		m_ResetTimer.Update(deltaTime);
		if (m_ResetTimer.IsExpired())
		{
			m_GameOver = false;
			m_ResetTimer.Reset();
		}
	}

	DeleteQueue();
}

void Scene::Render() noexcept
{
	RenderTexture(m_BackGround.GetTexture(), m_BackGround.GetTextureRectangle(), m_BackGround.GetRectangle());

 	if (!m_GameOver)
	{
		for (Entity* entity : m_Entities)
			::Render(*entity);
	}
}

void Scene::DestroyEntity(Entity* entity) noexcept
{
	assert(entity->IsNull() == false && "Entity is already destroyed");
	
	entity->m_IsNull = true;
	m_DelQueue.push_back(entity);
}

void Scene::Reset() noexcept
{
	for (Entity* entity : m_Entities)
	{
		if (!entity->IsNull())
			DestroyEntity(entity);
	}

	CreateEntity<Player>(m_SpriteLoader.GetSprite(SpriteType::Player), 2.0f, 2.0f);
	m_GameOver = true;
}

void Scene::LoadSprites() noexcept
{
	m_SpriteLoader.Load(SpriteType::Explosion, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/explosion.png", { 5, 1 });
	m_SpriteLoader.Load(SpriteType::Player, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/ship.png", { 5, 2 });
	m_SpriteLoader.Load(SpriteType::Bullet, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/laser-bolts.png", { 2, 2 });
	m_SpriteLoader.Load(SpriteType::Enemy, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/enemy-small.png", { 2, 1 });
}

void Scene::LoadSounds() noexcept
{
	m_SoundLoader.LoadWAV(SoundFXType::PlayerDied, "Assets/SoundFX/Explosion.wav");
	m_SoundLoader.LoadWAV(SoundFXType::EnemyDied, "Assets/SoundFX/EnemyDied.wav");
	m_SoundLoader.LoadWAV(SoundFXType::PlayerFire, "Assets/SoundFX/PlayerFire.wav");
	m_SoundLoader.LoadWAV(SoundFXType::EnemyFire, "Assets/SoundFX/EnemyFire.wav");
	m_SoundLoader.LoadMusic("Assets/Textures/space_shooter_pack/spaceship shooter music/spaceship shooter .ogg");
}

void Scene::LoadScene() noexcept
{
	m_BackGround.Init("Assets/Textures/space_shooter_pack/Graphics/backgrounds/desert-backgorund-looped.png", 1, 1);
	m_SoundLoader.PlayMusic();
	m_SpriteLoader.GetSprite(SpriteType::Player).SetFrameX(2);
	CreateEntity<Player>(m_SpriteLoader.GetSprite(SpriteType::Player), 2.0f, 2.0f);
}

void Scene::PhysicsUpdate() noexcept
{
	for (Entity* e1 : m_Entities)
	{
		if (e1->CheckTag("PhysicsEntity"))
		{
			for (Entity* e2 : m_Entities)
			{
				if (e2->CheckTag("PhysicsEntity") && e2 != e1)
				{
					if (CheckCollision(e2->GetRectangle(), e1->GetRectangle()))
					{
						static_cast<PhysicsEntity*>(e1)->OnCollision(*e2);
						static_cast<PhysicsEntity*>(e2)->OnCollision(*e1);
					}
				}
			}
		}
	}
}

void Scene::DeleteQueue() noexcept
{
	for (Entity* entity : m_DelQueue)
	{
		delete entity;
		m_Entities.remove(entity);
	}

	m_DelQueue.clear();
}
