#include "Game.h"
#include "Globals.h"
#include "Defines.h"
#include "Entities/Player.h"

#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

static void RenderTexture(SDL_Texture* texture, SDL_Rect* texRect, const SDL_FRect& rectangle) noexcept
{
	SDL_RenderCopyF(Globals::Renderer::Renderer, texture, texRect, &rectangle);
}

Game* Game::s_Instance = nullptr;

Game::Game() noexcept
{
	s_Instance = this;
    SDLInit();
	
	m_TimeStepMs = 1000.0f / GetDisplayMode().refresh_rate;
	m_TimeAccumulated = 0;

	LoadSprites();
	LoadSounds();
	LoadScene();

	ChangeSceneTo<MainMenu>();
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
		m_BackGround.Update(m_DeltaTime.GetDeltaTime());
		m_Scene->Update(m_DeltaTime.GetDeltaTime());

		if (m_Type == SceneType::MainMenu || m_Type == SceneType::HighScoreScene)
			SceneToggleUpdate(m_DeltaTime.GetDeltaTime());

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
	RenderTexture(m_BackGround.GetTexture(), &m_BackGround.GetTextureRectangle(), m_BackGround.GetRectangle());
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
			OnEscape(event);
		break;

		case SDL_SCANCODE_RETURN:
			OnReturn(event);

		default:
			break;
	}
}

void Game::OnReturn(const SDL_KeyboardEvent& event) noexcept
{
	switch(m_Type)
	{
		case SceneType::HighScoreScene:
		// case SceneType::MainMenu:
			ChangeSceneTo<TextInputScene>();
			break;

		default:
			break;
	}

}

void Game::OnEscape(const SDL_KeyboardEvent& event) noexcept
{
}

void Game::ProcessEvents(SDL_Event& event) noexcept
{
	m_Scene->ProcessEvents(event);

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
}

void Game::SceneToggleUpdate(float deltaTime) noexcept
{
	m_Timer.Update(deltaTime);
	if (m_Timer.IsExpired())
	{
		m_MenuToggle == false ? m_MenuToggle = true : m_MenuToggle = false;
		m_Timer.Reset();
	}

	if (m_MenuToggle)
	{
		if (m_Type != SceneType::HighScoreScene)
			ChangeSceneTo<HighScoreScene>();
	}
	else
	{
		if (m_Type != SceneType::MainMenu)
			ChangeSceneTo<MainMenu>();
	}
}

void Game::LoadSprites() noexcept
{
	m_SpriteLoader.Load(SpriteType::Explosion, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/explosion.png", { 5, 1 });
	m_SpriteLoader.Load(SpriteType::Player, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/ship.png", { 5, 2 });
	m_SpriteLoader.Load(SpriteType::Bullet, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/laser-bolts.png", { 2, 2 });
	m_SpriteLoader.Load(SpriteType::SmallEnemy, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/enemy-small.png", { 2, 1 });
	m_SpriteLoader.Load(SpriteType::MediumEnemy, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/enemy-medium.png", { 2, 1 });
	m_SpriteLoader.Load(SpriteType::BigEnemy, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/enemy-big.png", { 2, 1 });
	m_SpriteLoader.Load(SpriteType::PowerUp, "Assets/Textures/space_shooter_pack/Graphics/spritesheets/power-up.png", { 2, 2 });
}

void Game::LoadSounds() noexcept
{
	m_SoundLoader.LoadWAV(SoundFXType::PlayerDied, "Assets/SoundFX/Explosion.wav");
	m_SoundLoader.LoadWAV(SoundFXType::EnemyDied, "Assets/SoundFX/EnemyDied.wav");
	m_SoundLoader.LoadWAV(SoundFXType::PlayerFire, "Assets/SoundFX/PlayerFire.wav");
	m_SoundLoader.LoadWAV(SoundFXType::EnemyFire, "Assets/SoundFX/EnemyFire.wav");
	m_SoundLoader.LoadMusic("Assets/Textures/space_shooter_pack/spaceship shooter music/spaceship shooter .ogg");
}

void Game::LoadScene() noexcept
{
	m_TextRenderer.SetActiveFont("Assets/Fonts/Roboto-Medium.ttf", 28);
	m_BackGround.Init("Assets/Textures/space_shooter_pack/Graphics/backgrounds/desert-backgorund-looped.png", 1, 1);
	m_SoundLoader.PlayMusic();
	m_SpriteLoader.GetSprite(SpriteType::Player).SetFrameX(2);
}
