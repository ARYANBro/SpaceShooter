#include "Scene.h"

#include "Sprite.h"
#include "Entities/Player.h"
#include "Entities/Enemy.h"
#include "Entities/Bullet.h"
#include "Entities/PhysicsEntity.h"
#include "Entities/Explosion.h"
#include "EnemySpawner.h"

#include <cassert>

static void RenderTexture(SDL_Texture* texture, SDL_Rect* texRect, const SDL_FRect& rectangle) noexcept
{
	SDL_RenderCopyF(Globals::Renderer::Renderer, texture, texRect, &rectangle);
}

static void RenderSprite(Sprite& sprite, const SDL_FRect& rect) noexcept
{
	RenderTexture(sprite.GetTexture(), &sprite.GetRectangle(), rect);
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
	: m_Spawner(nullptr)
{
	s_Scene = this;
	m_Spawner = new EnemySpawner(2.0f, 3.0f);

	LoadSprites();
	LoadSounds();
	LoadScene();

	m_Font = TTF_OpenFont("Assets/Fonts/Roboto-Medium.ttf", 32);
	SDL_Surface* surface = TTF_RenderText_Blended(m_Font, "Hello World", SDL_Colour{ .r = 255, .g = 255, .b = 255, .a = 255 });
	m_Texture = SDL_CreateTextureFromSurface(Globals::Renderer::GetRenderer(), surface);
	SDL_FreeSurface(surface);
}

Scene::~Scene() noexcept
{
	for (Entity* entity : m_Entities)
		delete entity;

	delete m_Spawner;
}

void Scene::Update() noexcept
{
	m_DeltaTime.Update();
	m_BackGround.Update(m_DeltaTime.GetDeltaTime());

	if (!GetGameOver())
	{
		m_Spawner->Update(m_DeltaTime.GetDeltaTime());
		PhysicsUpdate();

		for (Entity* entity : m_Entities)
			entity->Update(m_DeltaTime.GetDeltaTime());
	}
	else
	{
		m_ResetTimer.Update(m_DeltaTime.GetDeltaTime());
		if (m_ResetTimer.IsExpired())
		{
			SetGameOver(false);
			m_ResetTimer.Reset();
		}
	}

	DeleteQueue();
}

void Scene::Render() noexcept
{
	RenderTexture(m_BackGround.GetTexture(), &m_BackGround.GetTextureRectangle(), m_BackGround.GetRectangle());

	int w, h;
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &w, &h);
	SDL_FRect rect = {
		.x = Globals::Window::Width / 2,
		.y = Globals::Window::Height / 2,
		.w = w,
		.h = h
	};

	RenderTexture(m_Texture, nullptr, rect);

 	if (!GetGameOver())
	{
		for (Entity* entity : m_Entities)
		{
			if (!entity->Hidden())
				::Render(*entity);
		}
	}
}

void Scene::DestroyEntity(Entity* entity) noexcept
{
	if (!entity->IsNull())
	{
		entity->m_IsNull = true;
		m_DelQueue.push_back(entity);
	}
}

void Scene::Reset() noexcept
{
	for (Entity* entity : m_Entities)
	{
		if (!entity->IsNull())
			DestroyEntity(entity);
	}

	CreateEntity<Player>(m_SpriteLoader.GetSprite(SpriteType::Player), 2.0f, 2.0f);
	SetGameOver(true);
}

void Scene::LoadSprites() noexcept
{
	m_SpriteLoader.Load(SpriteType::Explosion, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/explosion.png", { 5, 1 });
	m_SpriteLoader.Load(SpriteType::Player, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/ship.png", { 5, 2 });
	m_SpriteLoader.Load(SpriteType::Bullet, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/laser-bolts.png", { 2, 2 });
	m_SpriteLoader.Load(SpriteType::SmallEnemy, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/enemy-small.png", { 2, 1 });
	m_SpriteLoader.Load(SpriteType::MediumEnemy, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/enemy-medium.png", { 2, 1 });
	m_SpriteLoader.Load(SpriteType::BigEnemy, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/enemy-big.png", { 2, 1 });
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
						static_cast<PhysicsEntity*>(e1)->OnCollision(*e2);
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
