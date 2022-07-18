#include "GameScene.h"

#include "EnemySpawner.h"
#include "Entities/Player.h"


GameScene::GameScene() noexcept
    : m_Spawner(nullptr)
{
	m_Spawner = new EnemySpawner(2.0f, 3.0f);
    CreateEntity<Player>(GetSpriteLoader().GetSprite(SpriteType::Player), 2.0f, 2.0f);
    m_GetInput = true;
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
    else if (m_GetInput)
    {
        SetRenderEntities(false);
        SetUpdateEntities(false);
        GetTextRenderer().RenderText("Enter your name:", { Globals::Window::Width / 2.0f, Globals::Window::Height / 2.0f - 200});
        GetTextRenderer().RenderText(m_InputText, { Globals::Window::Width / 2.0f, Globals::Window::Height / 2.0f - 50.0f});
    }
    else
    {
		m_Spawner->Update(deltaTime);
        SetRenderEntities(true);
        SetUpdateEntities(true);

    	GetTextRenderer().RenderText("Score: " + std::to_string(m_Score), { 0.0f, 0.0f });

        static auto found = std::find_if(GetEntities().begin(), GetEntities().end(), [](Entity* entity) { return entity->CheckTag("Player"); });
        if (found != GetEntities().end())
        {
            const std::string& name = static_cast<Player*>((*found))->GetName();
            GetTextRenderer().RenderText("Player Name: " + name, { 0.0f, 100.0f });

        }
    }
}

void GameScene::ProcessEvents(SDL_Event& event) noexcept
{
    switch (event.type)
    {
        case SDL_TEXTINPUT:
        {
            m_InputText += event.text.text;
            break;
        }

        if (m_GetInput)
        {
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_BACKSPACE:
                    {
                        if (m_InputText.size() > 0)
                            m_InputText.erase(m_InputText.size() - 1);

                        break;
                    }

                    case SDL_SCANCODE_RETURN:
                    {
                        auto found = std::find_if(GetEntities().begin(), GetEntities().end(), [](Entity* entity) { return entity->CheckTag("Player"); });
                        if (found != GetEntities().end())
                            static_cast<Player*>((*found))->SetName(m_InputText);

                        m_GetInput = false;
                        break;
                    }
                }

                break;
            }
        }
    }
}

void GameScene::IncreaseScore() noexcept
{
    m_Score++;
}