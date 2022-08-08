#pragma once

#include "DeltaTime.h"
#include "MenuScene.h"

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

private:
    enum class SceneType
    {
        GameScene, MenuScene, TextInputScene
    };

private:
    Scene* m_Scene;
    SceneType m_Type;
    DeltaTime m_DeltaTime;
    float m_TimeStepMs;
	int m_TimeAccumulated;
    bool m_Running = true;
    std::string m_PlayerName = std::string();

private:
    void SDLDeinit() noexcept;
    void InitWindow() noexcept;
    void InitRenderer() noexcept;
    void SDLInit() noexcept;
    void BeginRender() noexcept;
    void EndRender() noexcept;
    SDL_DisplayMode GetDisplayMode() noexcept;
    void OnKeyDown(const SDL_KeyboardEvent& event) noexcept;
    void ProcessEvents(SDL_Event& event) noexcept;

    template<typename SceneType> requires std::is_base_of_v<Scene, SceneType>
    void ChangeSceneTo() noexcept;
};

#include "Game.inl"