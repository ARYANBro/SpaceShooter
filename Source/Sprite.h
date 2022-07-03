#pragma once

#include <string>

#include <SDL2/SDL_image.h>

class Sprite
{
public:
	Sprite() noexcept = default;
	Sprite(Sprite& sprite) noexcept;
	~Sprite() noexcept;

	Sprite(const std::string& path, int numXFrames, int numYFrames) noexcept;

	void Load(const std::string& path, int numXFrames, int numYFrames) noexcept;
	void SetFrameX(int x) noexcept;
	void SetFrameY(int y) noexcept;
	void SetRectPosition(float x, float y) noexcept { m_SourceRect.x = x; m_SourceRect.y = y; }
	void SetRectScale(float width, float height) noexcept { m_SourceRect.w = width; m_SourceRect.h = height; }

	int GetFrameX() const noexcept { return m_SourceRect.x; }
	int GetFrameY() const noexcept { return m_SourceRect.y; }
	SDL_Rect& GetRectangle() noexcept { return m_SourceRect; }
	SDL_Texture* GetTexture() const noexcept { return m_Texture; }
	int GetTextureWidth() const noexcept { return m_TexWidth; }
	int GetTextureHeight() const noexcept { return m_TexHeight; }
 	int GetFrameWidth() const noexcept { return m_TexWidth / m_NumFramesX; }
	int GetFrameHeight() const noexcept { return m_TexHeight/ m_NumFramesY; }
	int GetNumFramesX() const noexcept { return m_NumFramesX; }
	int GetNumFramesY() const noexcept { return m_NumFramesY; }

	Sprite& operator=(Sprite& other) noexcept;
	Sprite& operator=(Sprite&& other) noexcept;

private:
	int m_NumFramesX;
	int m_NumFramesY;
	SDL_Texture* m_Texture;
	int m_TexWidth, m_TexHeight;
	SDL_Rect m_SourceRect;

private:	
	SDL_Texture* LoadTexture(const std::string& path) noexcept;
};
