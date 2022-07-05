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

	m_TexRect.w = m_TexWidth;
	m_TexRect.h  = m_TexHeight;

	m_Rect.w = (Globals::Window::Width / m_TexWidth) * m_TexWidth;
	m_Rect.h = (Globals::Window::Width / m_TexWidth) * m_TexHeight;

	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_TexWidth, &m_TexHeight);
}

void ScrollingBackGround::Update(double deltaTime) noexcept
{
	m_Rect.y += deltaTime * 200;
	if (m_Rect.y >= 0.0)
		m_Rect.y = GetTileHeight() - m_Rect.h;
}
