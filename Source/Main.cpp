#include "Defines.h"
#include "Sprite.h"
#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "EnemySpawner.h"
#include "Globals.h"
#include "Scene.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <cassert>
#include <string>
#include <algorithm>
#include <map>
#include <concepts>
#include <list>

static bool g_Running = true;
static Sprite g_BulletSprite;

static void SDLDeinit() noexcept
{
	SDL_DestroyWindow(Globals::Window::GetWindow());
	SDL_DestroyRenderer(Globals::Renderer::Renderer);
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();	
	SDL_Quit();
}

static void PollEvents() noexcept
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				g_Running = false;
				break;

			default:
				break;
		}
	}
}

static void InitWindow() noexcept
{
	Globals::Window::Window = SDL_CreateWindow("3DGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::Window::Width, Globals::Window::Height, 0);
	CHECK_SDL_ERROR(Globals::Window::GetWindow() != nullptr)
}

static void InitRenderer() noexcept
{
	SDL_RenderSetLogicalSize(Globals::Renderer::GetRenderer(), Globals::Renderer::RenderWidth, Globals::Renderer::RenderHeight);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

	Globals::Renderer::Renderer = SDL_CreateRenderer(Globals::Window::GetWindow(), -1, SDL_RENDERER_ACCELERATED);
	CHECK_SDL_ERROR(Globals::Renderer::GetRenderer() != nullptr)
}

static void SDLInit() noexcept
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

static void BeginRender() noexcept
{
	SDL_SetRenderDrawColor(Globals::Renderer::Renderer, 10, 10, 15, 255);
	SDL_RenderClear(Globals::Renderer::Renderer);
}

static void EndRender() noexcept
{
	SDL_RenderPresent(Globals::Renderer::Renderer);
}

int main()
{
	SDLInit();

	Scene scene;

	while (g_Running)
	{
		PollEvents();
		scene.Update();
		BeginRender();
		scene.Render();
		EndRender();
	}

	SDLDeinit();
}
