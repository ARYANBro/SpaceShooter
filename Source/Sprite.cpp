#include "Sprite.h"

#include "Defines.h"
#include "Globals.h"

#include <algorithm>

Sprite::Sprite(const std::string& path, int numXFrames, int numYFrames) noexcept
{
	Load(path, numXFrames, numYFrames);
}

Sprite::Sprite(Sprite& sprite) noexcept
	: m_NumFramesX(sprite.m_NumFramesX), m_NumFramesY(sprite.m_NumFramesY), m_Texture(sprite.m_Texture), m_TexWidth(sprite.m_TexWidth),
	m_TexHeight(sprite.m_TexHeight), m_SourceRect(sprite.m_SourceRect)
{
	sprite.m_Texture = nullptr;
}

Sprite::~Sprite() noexcept
{
	SDL_DestroyTexture(m_Texture);
}

void Sprite::Load(const std::string& path, int numXFrames, int numYFrames) noexcept
{
	assert(numXFrames > 0);
	assert(numYFrames > 0);

	m_NumFramesX = numXFrames;
	m_NumFramesY = numYFrames;
	m_Texture = LoadTexture(path);

	SetRectPosition(0, 0);
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_TexWidth, &m_TexHeight);
	SetRectScale(m_TexWidth / numXFrames, m_TexHeight / numYFrames);
}

void Sprite::SetFrameX(int x) noexcept
{
	m_SourceRect.x = std::clamp(x * m_SourceRect.w, 0, (m_NumFramesX - 1) * m_SourceRect.w);
}

void Sprite::SetFrameY(int y) noexcept
{
	m_SourceRect.y = std::clamp(y * m_SourceRect.h, 0, (m_NumFramesY - 1) * m_SourceRect.h);
}

SDL_Texture* Sprite::LoadTexture(const std::string& path) noexcept
{	
	SDL_Texture* texture = IMG_LoadTexture(Globals::Renderer::GetRenderer(), path.c_str());
	CHECK_SDL_IMAGE_ERROR(texture != nullptr);
	return texture;
}

Sprite& Sprite::operator=(Sprite& other) noexcept
{
	Sprite temp(other);
	*this = std::move(temp);
	return *this;
}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
	if (this != &other)
	{
		m_NumFramesX = other.m_NumFramesX;
		m_NumFramesY = other.m_NumFramesY;
		m_Texture = other.m_Texture;
		m_TexWidth = other.m_TexWidth;
		m_TexHeight = other.m_TexHeight;
		m_SourceRect = other.m_SourceRect;

		other.m_Texture = nullptr;
	}

	return *this;
}