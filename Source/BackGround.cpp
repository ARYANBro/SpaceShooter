#include "BackGround.h"

#include "Globals.h"
#include "Sprite.h"
#include "Defines.h"

ScrollingBackGround::ScrollingBackGround(const std::string& texturePath, int tileX, int tileY) noexcept
{
	Init(texturePath, tileX, tileY);
}

ScrollingBackGround::~ScrollingBackGround() noexcept
{
	SDL_DestroyTexture(m_Texture);
}

void ScrollingBackGround::Init(const std::string& texturePath, int tileX, int tileY) noexcept
{
	assert(!m_Texture);
	m_TileX = tileX;
	m_TileY = tileY;

	m_Texture = IMG_LoadTexture(Globals::Renderer::GetRenderer(), texturePath.c_str());
	CHECK_SDL_IMAGE_ERROR(m_Texture != nullptr);

	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_TexWidth, &m_TexHeight);

	m_TexRect.w = GetTileWidth();
	m_TexRect.h  = GetTileHeight();

	m_Rect.w = Globals::Window::Width;
	m_Rect.h = Globals::Window::Height;
}

void ScrollingBackGround::Update() noexcept
{
	if (--m_TexRect.y <= 0)
		m_TexRect.y = GetTileHeight();
}
