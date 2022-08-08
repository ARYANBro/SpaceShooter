#pragma once

#include <SDL_mixer.h>

#include <array>
#include <string>
#include <cassert>

enum class SoundFXType
{
	PlayerFire, EnemyFire, EnemyDied, PlayerDied
};

class SoundLoader
{
public:
	~SoundLoader() noexcept;

	void LoadWAV(SoundFXType type, const std::string& path) noexcept;
	void LoadMusic(const std::string& path) noexcept;
	void PlaySound(SoundFXType type) const noexcept;
	void PlayMusic(int numLoops = -1) const noexcept;
	void StopMusic() const noexcept;

private:
	std::array<Mix_Chunk*, 8> m_SoundFX { nullptr };
	Mix_Music* m_Music = nullptr;
};