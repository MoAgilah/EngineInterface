#include "SoundManager.h"

#include "../Core/Constants.h"

SoundManager::SoundManager()
	: m_soundLoader(GameConstants::SoundFilePaths),
	m_musicLoader(GameConstants::MusicFilePaths)
{}

ISound* SoundManager::GetSound(const std::string& name)
{
	return m_soundLoader.GetResource(name);
}

IMusic* SoundManager::GetMusic(const std::string& name)
{
	return m_musicLoader.GetResource(name);
}

void SoundManager::AddSounds(const fs::path& path)
{
	m_soundLoader.LoadResources(path);
}

void SoundManager::AddMusic(const fs::path& path)
{
	m_musicLoader.LoadResources(path);
}