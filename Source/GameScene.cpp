#include "GameScene.h"

#include "EnemySpawner.h"
#include "Entities/Player.h"

GameScene::GameScene(const std::string& playerName) noexcept
    : m_Spawner(nullptr)
{
	m_Spawner = new EnemySpawner(2.0f, 3.0f);
    Player& player = CreateEntity<Player>(GetSpriteLoader().GetSprite(SpriteType::Player), 2.0f, 2.0f, playerName);
}

GameScene::~GameScene()
{
    delete m_Spawner;
}

void GameScene::Reset() noexcept
{
    std::string playerName;
    if (Player* player = GetPlayer())
        playerName = player->GetName();
    Scene::Reset();
    SetGameOver(true);
    ResetScore();
	CreateEntity<Player>(GetSpriteLoader().GetSprite(SpriteType::Player), 2.0f, 2.0f, playerName);
}

void GameScene::Update(float deltaTime) noexcept
{
    Scene::Update(deltaTime);

    RenderHud();
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
    {
		m_Spawner->Update(deltaTime);
        SetRenderEntities(true);
        SetUpdateEntities(true);
    }
}

void GameScene::ProcessEvents(SDL_Event& event) noexcept
{
}

void GameScene::IncreaseScore() noexcept
{
    m_Score++;
}

Player* GameScene::GetPlayer() noexcept
{
    auto found = std::find_if(GetEntities().begin(), GetEntities().end(), [](Entity* entity) { return entity->CheckTag("Player"); });
    if (found != GetEntities().end())
        return static_cast<Player*>(*found);
    
    return nullptr;
}

void GameScene::RenderHud() noexcept
{
    GetTextRenderer().RenderText("Score: " + std::to_string(m_Score), { 0.0f, 0.0f });

        if (Player* player = GetPlayer())
            GetTextRenderer().RenderText("Player Name: " + player->GetName(), { 0.0f, 100.0f });
}