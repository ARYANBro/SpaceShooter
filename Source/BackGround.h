#pragma once

#include "Entities/Entity.h"

#include <string>

class ScrollingBackGround
{
public:
	ScrollingBackGround() noexcept = default;
	ScrollingBackGround(const std::string& texturePath, int tileX, int tileY) noexcept;
	~ScrollingBackGround() noexcept;

	void Init(const std::string& texturePath, int tileX, int tileY) noexcept;
	void Update(double deltaTime) noexcept;

	int GetTileWidth() const noexcept { return m_TexWidth / m_TileX; }
	int GetTileHeight() const noexcept { return m_TexHeight / m_TileY; }

	SDL_Texture* GetTexture() const noexcept { return m_Texture; }
	const SDL_Rect& GetTextureRectangle() const noexcept { return m_TexRect; }
	const SDL_FRect& GetRectangle() const noexcept { return m_Rect; }

	SDL_Rect& GetTextureRectangle() noexcept { return m_TexRect; }
	SDL_FRect& GetRectangle() noexcept { return m_Rect; }

private:
	int m_TileX, m_TileY;
	double m_TexRectY;
	SDL_Texture* m_Texture = nullptr;
	int m_TexWidth, m_TexHeight;
	SDL_Rect m_TexRect = SDL_Rect();
	SDL_FRect m_Rect = SDL_FRect();
};