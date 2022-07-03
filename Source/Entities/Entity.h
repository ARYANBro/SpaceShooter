#pragma once

#include <SDL2/SDL.h>
#include <cassert>
#include <string>
#include <array>

class Sprite;

class Entity
{
public:
	Entity(Sprite& sprite, int scaleX = 1, int scaleY = 1) noexcept;
	virtual ~Entity() noexcept = default;

	virtual void Update() {}

	void SetSpeedX(float speedX) noexcept { m_SpeedX = speedX; }
	void SetSpeedY(float speedY) noexcept { m_SpeedY = speedY; }
	void SetActiveFrameX(int frame) noexcept { m_ActiveFrameX = frame; }
	void SetActiveFrameY(int frame) noexcept { m_ActiveFrameY = frame; }
	void AddTag(const std::string& tag) { assert(m_TagIndex < 8); m_Tags[m_TagIndex++] = tag; }

	bool IsNull() const noexcept { return m_IsNull; }
	const SDL_FRect& GetRectangle() const noexcept { return m_Rect; }
	const Sprite& GetSprite() const noexcept { return m_Sprite; }
	Sprite& GetSprite() noexcept { return m_Sprite; }
	float GetSpeedX() const noexcept { return m_SpeedX; }
	float GetSpeedY() const noexcept { return m_SpeedY; }
	int GetActiveFrameX() const noexcept { return m_ActiveFrameX; }
	int GetActiveFrameY() const noexcept { return m_ActiveFrameY; }

	SDL_FRect& GetRectangle() noexcept { return m_Rect; }
	const std::array<std::string, 8>& GetTags() const noexcept { return m_Tags; }
	bool CheckTag(const std::string& tag) const noexcept;
private:
	friend class Scene;

private:
	std::array<std::string, 8> m_Tags;
	int m_TagIndex = 0;
	bool m_IsNull = false;
	SDL_FRect m_Rect = SDL_FRect();
	Sprite& m_Sprite;
	float m_SpeedX = 0.0f;
	float m_SpeedY = 0.0f;
	int m_ActiveFrameX = 0;
	int m_ActiveFrameY = 0;
};