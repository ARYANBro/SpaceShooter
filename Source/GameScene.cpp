#include "GameScene.h"

#include "EnemySpawner.h"
#include "Entities/Player.h"


GameScene::GameScene() noexcept
    : m_Spawner(nullptr)
{
	m_Spawner = new EnemySpawner(2.0f, 3.0f);
    CreateEntity<Player>(GetSpriteLoader().GetSprite(SpriteType::Player), 2.0f, 2.0f);
}

GameScene::~GameScene()
{
    delete m_Spawner;
}

void GameScene::Reset() noexcept
{
    Scene::Reset();
    SetGameOver(true);
    ResetScore();
	CreateEntity<Player>(GetSpriteLoader().GetSprite(SpriteType::Player), 2.0f, 2.0f);
}

void GameScene::Update(float deltaTime) noexcept
{
    Scene::Update(deltaTime);
	GetTextRenderer().RenderText("Score: " + std::to_string(m_Score), { 0.0f, 0.0f });

    if (m_GameOver)
    {
        SetRenderEntities(false);
        SetUpdateEntities(false);
        m_ResetTimer.Update(deltaTime);

		if (m_ResetTimer.IsExpired())
		{
            SetRenderEntities(true);
            SetUpdateEntities(true);
			SetGameOver(false);
			m_ResetTimer.Reset();
		}
    }
    else
		m_Spawner->Update(deltaTime);

    // return deltaTime;
}

void GameScene::IncreaseScore() noexcept
{
    m_Score++;
}