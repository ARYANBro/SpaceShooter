#include "Scene.h"

#include "Game.h"
#include "Sprite.h"
#include "Globals.h"
#include "Entities/PhysicsEntity.h"

#include <cassert>
#include <fstream>
#include <iostream>

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

Scene::Scene() noexcept
{
}

Scene::~Scene() noexcept
{
	for (Entity* entity : m_Entities)
		delete entity;
}

void Scene::Update(float deltaTime) noexcept
{
	if (m_UpdateEntities)
	{
		PhysicsUpdate();

		for (Entity* entity : m_Entities)
		{
			if (entity)
				entity->Update(deltaTime);
		}
	}

	DeleteQueue();
}

void Scene::Render() noexcept
{
 	if (m_RenderEntities)
	{
		for (Entity* entity : m_Entities)
		{
			if (entity)
			{
				if (!entity->Hidden())
					::Render(*entity);
			}
		}
	}

	Game::GetInstance().GetTextRenderer().RenderQueue();
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
}

void Scene::PhysicsUpdate() noexcept
{
	for (Entity* e1 : m_Entities)
	{
		if (e1)
		{
			if (e1->CheckTag("PhysicsEntity"))
			{
				for (Entity* e2 : m_Entities)
				{
					if (e2)
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