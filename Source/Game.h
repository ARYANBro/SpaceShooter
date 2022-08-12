#pragma once

#include "DeltaTime.h"
#include "Timer.h"
#include "BackGround.h"
#include "SoundLoader.h"
#include "SpriteLoader.h"
#include "TextRenderer.h"

#include <SDL.h>

#include <string>
#include <cassert>

class Scene;

class Game
{
public:
    Game() noexcept;
    ~Game() noexcept;

    void Update() noexcept;
    void ProcessInput() noexcept;
    void Render() noexcept;
    Scene& GetScene() noexcept { return *m_Scene; }
    const Scene& GetScene() const noexcept { return *m_Scene; }

    SpriteLoader& GetSpriteLoader() noexcept { return m_SpriteLoader; }
	SoundLoader& GetSoundLoader() noexcept { return m_SoundLoader; } 
	TextRenderer& GetTextRenderer() noexcept { return m_TextRenderer; }

    void SetPlayerName(const std::string& playerName) noexcept { m_PlayerName = playerName; }
    const std::string& GetPlayerName() const noexcept { return m_PlayerName; }
    static Game& GetInstance() noexcept { return *s_Instance; }

    template<typename SceneType> requires std::is_base_of_v<Scene, SceneType>
    void ChangeSceneTo() noexcept;

private:
    enum class SceneType
    {
        GameScene, HighScoreScene, TextInputScene, MainMenu
    };

private:
    static Game* s_Instance;
    Scene* m_Scene = nullptr;
    SceneType m_Type;
    DeltaTime m_DeltaTime;
    float m_TimeStepMs;
	int m_TimeAccumulated;
    bool m_Running = true;
    std::string m_PlayerName = std::string();
    Timer m_Timer = { 7.0f };
    bool m_MenuToggle = false;

    SpriteLoader m_SpriteLoader;
	SoundLoader m_SoundLoader;
	TextRenderer m_TextRenderer;
	ScrollingBackGround m_BackGround;

private:
    void SDLDeinit() noexcept;
    void InitWindow() noexcept;
    void InitRenderer() noexcept;
    void SDLInit() noexcept;
    void BeginRender() noexcept;
    void EndRender() noexcept;
    SDL_DisplayMode GetDisplayMode() noexcept;
    void OnKeyDown(const SDL_KeyboardEvent& event) noexcept;
    void OnReturn(const SDL_KeyboardEvent& event) noexcept;
    void OnEscape(const SDL_KeyboardEvent& event) noexcept;
    void ProcessEvents(SDL_Event& event) noexcept;
    void SceneToggleUpdate(float deltaTime) noexcept;

    void LoadSprites() noexcept;
	void LoadSounds() noexcept;
	void LoadScene() noexcept;
};

#include "Game.inl"