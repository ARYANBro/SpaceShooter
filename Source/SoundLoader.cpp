#include "SoundLoader.h"

SoundLoader::~SoundLoader() noexcept
{
	for (Mix_Chunk* sfx : m_SoundFX)
		Mix_FreeChunk(sfx);

	Mix_FreeMusic(m_Music);
}

void SoundLoader::LoadWAV(SoundFXType type, const std::string& path) noexcept
{
	m_SoundFX[static_cast<int>(type)] = Mix_LoadWAV(path.c_str());
}

void SoundLoader::LoadMusic(const std::string& path) noexcept
{
	m_Music = Mix_LoadMUS(path.c_str());
}

void SoundLoader::PlaySound(SoundFXType type) const noexcept
{
	switch (type)
	{
		case SoundFXType::PlayerFire:
		case SoundFXType::PlayerDied:
			Mix_PlayChannel(0, m_SoundFX[static_cast<int>(type)], 0);
			break;

		case SoundFXType::EnemyFire:
		case SoundFXType::EnemyDied:
			Mix_PlayChannel(1, m_SoundFX[static_cast<int>(type)], 0);
			break;

		default:
			assert(false);
	}
}

void SoundLoader::PlayMusic(int numLoops) const noexcept
{
	assert(m_Music);
	Mix_PlayMusic(m_Music, numLoops);
}

void SoundLoader::StopMusic() const noexcept 
{
	Mix_HaltMusic();
}