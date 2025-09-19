#pragma once

#include "../Interface/Resources/IMusic.h"
#include "../Interface/Resources/ISound.h"
#include "../../Utilities/ResourceLoader.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager() = default;

	ISound* GetSound(const std::string& name);
	IMusic* GetMusic(const std::string& name);

	void AddSounds(const fs::path& path);
	void AddMusic(const fs::path& path);

private:

	ResourceLoader<ISound> m_soundLoader;
	ResourceLoader<IMusic> m_musicLoader;
};