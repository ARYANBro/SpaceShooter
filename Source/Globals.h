#pragma once

#include <SDL.h>

namespace Globals
{
	namespace Window
	{
		inline constexpr int Width = 512;
		inline constexpr int Height = 544;

		extern SDL_Window* Window;

		inline SDL_Window* GetWindow() noexcept { return Window; }
	}

	namespace Renderer
	{
		inline constexpr int RenderWidth = 256;
		inline constexpr int RenderHeight = 272;

		extern SDL_Renderer* Renderer;

		inline SDL_Renderer* GetRenderer() noexcept { return Renderer; }
	}
}
