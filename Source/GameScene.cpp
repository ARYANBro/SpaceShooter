#include "GameScene.h"

#include "HighScoreScene.h"
#include "EnemySpawner.h"
#include "Entities/Player.h"
#include "Game.h"

GameScene::GameScene(const std::string& playerName) noexcept
    : m_Spawner(nullptr)
{
	m_Spawner = new EnemySpawner(2.0f, 3.0f);
    Player& player = CreateEntity<Player>(Game::GetInstance().GetSpriteLoader().GetSprite(SpriteType::Player), 2.0f, 2.0f, playerName);
}

GameScene::~GameScene()
{
    delete m_Spawner;
}

void GameScene::Reset() noexcept
{
    if (m_Score > m_HighScore)
        m_HighScore = m_Score;
        
    std::string playerName;
    if (Player* player = GetPlayer())
        playerName = player->GetName();
    Scene::Reset();
    SetGameOver(true);
    ResetScore();
	CreateEntity<Player>(Game::GetInstance().GetSpriteLoader().GetSprite(SpriteType::Player), 2.0f, 2.0f, playerName);
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
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    // Game::GetInstance().SetPlayerName(GetPlayer()->GetName());
                    Game::GetInstance().ChangeSceneTo<HighScoreScene>();
                    break;
                
                default:
                    break;
            }

            break;
        }

        default:
        break;
    }
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
    Game::GetInstance().GetTextRenderer().RenderText("Score: " + std::to_string(m_Score), { 0.0f, 0.0f });

    if (Player* player = GetPlayer())
        Game::GetInstance().GetTextRenderer().RenderText("Player Name: " + player->GetName(), { 0.0f, 100.0f });
}