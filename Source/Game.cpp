#include "Game.h"
#include "Globals.h"
#include "Defines.h"
#include "Entities/Player.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

Game::Game() noexcept
{
    SDLInit();
	
	m_TimeStepMs = 1000.0f / GetDisplayMode().refresh_rate;
	m_TimeAccumulated = 0;

	m_Type = SceneType::MenuScene;
	m_Scene = new MenuScene();
}

Game::~Game() noexcept
{
    delete m_Scene;
	SDLDeinit();

}

void Game::Update() noexcept
{
    while (m_Running)
	{
        m_DeltaTime.Update();
        ProcessInput();
		m_Scene->Update(m_DeltaTime.GetDeltaTime());
        Render();
	}
}

void Game::ProcessInput() noexcept
{
    m_TimeAccumulated += m_DeltaTime.GetDeltaTime();

    if (m_TimeAccumulated <= m_TimeStepMs)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        ProcessEvents(event);
        m_TimeAccumulated = 0.0f;
    }
}

void Game::Render() noexcept
{
    BeginRender();
    m_Scene->Render();
    EndRender();
}

void Game::SDLDeinit() noexcept
{
	SDL_DestroyWindow(Globals::Window::GetWindow());
	SDL_DestroyRenderer(Globals::Renderer::Renderer);
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();	
	SDL_Quit();
}

void Game::InitWindow() noexcept
{
	Globals::Window::Window = SDL_CreateWindow("3DGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::Window::Width, Globals::Window::Height, 0);
	CHECK_SDL_ERROR(Globals::Window::GetWindow() != nullptr)
}

void Game::InitRenderer() noexcept
{
	SDL_RenderSetLogicalSize(Globals::Renderer::GetRenderer(), Globals::Renderer::RenderWidth, Globals::Renderer::RenderHeight);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

	Globals::Renderer::Renderer = SDL_CreateRenderer(Globals::Window::GetWindow(), -1, SDL_RENDERER_ACCELERATED);
	CHECK_SDL_ERROR(Globals::Renderer::GetRenderer() != nullptr)
}

void Game::SDLInit() noexcept
{
	int sdlInitResult = SDL_Init(SDL_INIT_EVERYTHING);
	CHECK_SDL_ERROR(sdlInitResult == 0)

	int imgInitResult = IMG_Init(IMG_INIT_PNG);
	CHECK_SDL_IMAGE_ERROR(imgInitResult != 0);

	int mixInitResult = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	CHECK_SDL_MIXER_ERROR(mixInitResult != -1);

	int ttfInitResult = TTF_Init();
	CHECK_SDL_TTF_ERROR(ttfInitResult == 0);

	Mix_AllocateChannels(8);

	InitWindow();
	InitRenderer();
}

void Game::BeginRender() noexcept
{
	SDL_SetRenderDrawColor(Globals::Renderer::Renderer, 10, 10, 15, 255);
	SDL_RenderClear(Globals::Renderer::Renderer);
}

void Game::EndRender() noexcept
{
	SDL_RenderPresent(Globals::Renderer::Renderer);
}

SDL_DisplayMode Game::GetDisplayMode() noexcept
{	
	SDL_DisplayMode dp;
	SDL_GetDesktopDisplayMode(SDL_GetWindowDisplayIndex(Globals::Window::Window), &dp);
	return dp;
}

void Game::OnKeyDown(const SDL_KeyboardEvent& event) noexcept
{
	switch (event.keysym.scancode)
	{
		case SDL_SCANCODE_ESCAPE:
			if (m_Type == SceneType::GameScene)
				ChangeSceneTo<MenuScene>();
			else if (m_Type == SceneType::MenuScene)
			{
				if (m_PlayerName.empty())
					ChangeSceneTo<TextInputScene>();
				else
					ChangeSceneTo<GameScene>();
			}
		break;

		case SDL_SCANCODE_RETURN:
			if (m_Type == SceneType::TextInputScene)
			{
				TextInputScene* tiScene = static_cast<TextInputScene*>(m_Scene);
				m_PlayerName = tiScene->GetInputText();

				ChangeSceneTo<GameScene>();
			}

		default:
			break;
	}
}

void Game::ProcessEvents(SDL_Event& event) noexcept
{
    switch (event.type)
    {
        case SDL_QUIT:
            m_Running = false;
            break;

        case SDL_KEYDOWN:
			OnKeyDown(event.key);

            break;
        default:
            break;
    }

	m_Scene->ProcessEvents(event);
}