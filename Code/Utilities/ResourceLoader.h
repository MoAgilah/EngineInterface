#pragma once

#include "../Engine/Core/Constants.h"
#include "../Engine/Interface/Resources/IFont.h"
#include "../Engine/Interface/Resources/IShader.h"
#include "../Engine/Interface/Resources/IMusic.h"
#include "../Engine/Interface/Resources/ITexture.h"
#include "../Engine/Interface/Resources/ISound.h"
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

template<typename T>
class ResourceLoader
{
public:
	explicit ResourceLoader(const std::string& path) { LoadResources(path); }
	ResourceLoader() = default;
	virtual ~ResourceLoader() = default;

	T* GetResource(const std::string& name);

	void LoadResources(const fs::path& path);

private:
	std::unordered_map<std::string, std::unique_ptr<T>> m_resources;

	bool IsValidDirectory(const fs::path& path) const;
	std::string GetCleanName(const fs::path& path) const;
};

// General Resource Loader
template<typename T>
void ResourceLoader<T>::LoadResources(const fs::path& path)
{
}

#if USE_SFML
// Specialisation for IFont
template<>
inline void ResourceLoader<IFont>::LoadResources(const fs::path& path)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		auto font = ActiveFontTrait::Create();

		if (!font->LoadFromFile(entry.path().string()))
		{
			std::cerr << "Failed to load font: " << entry.path() << "\n";
			continue;
		}

		m_resources.emplace(entry.path().filename().replace_extension().string(),
			std::move(font));
	}
}

template<>
inline void ResourceLoader<IMusic>::LoadResources(const fs::path& path)
{
	if (!fs::exists(path) || !fs::is_directory(path)) return;

	for (const auto& entry : fs::directory_iterator(path))
	{
		auto music = ActiveMusicTrait::Create();

		if (!music->LoadFromFile(entry.path().string()))
		{
			std::cerr << "Failed to load music: " << entry.path() << "\n";
			continue;
		}
		m_resources.emplace(entry.path().filename().replace_extension().string(), std::move(music));
	}
}

template<>
inline void ResourceLoader<ISound>::LoadResources(const fs::path& path)
{
	if (!fs::exists(path) || !fs::is_directory(path)) return;

	for (const auto& entry : fs::directory_iterator(path))
	{
		auto sound = ActiveSoundTrait::Create();

		if (!sound->LoadFromFile(entry.path().string()))
		{
			std::cerr << "Failed to load music: " << entry.path() << "\n";
			continue;
		}
		m_resources.emplace(entry.path().filename().replace_extension().string(), std::move(sound));
	}
}

template<>
inline void ResourceLoader<IShader>::LoadResources(const fs::path& path)
{

	if (!fs::exists(path) || !fs::is_directory(path))
		return;

	for (const auto& entry : fs::directory_iterator(path))
	{
		auto shader = ActiveShaderTrait::Create();
		if (!shader->LoadFromFile(entry.path().string()))
		{
			std::cerr << "Failed to load shader: " << entry.path() << "\n";
			continue;
		}
		m_resources.emplace(entry.path().filename().replace_extension().string(), std::move(shader));
	}
}

template<>
inline void ResourceLoader<ITexture>::LoadResources(const fs::path& path)
{

	if (!fs::exists(path) || !fs::is_directory(path))
		return;

	for (const auto& entry : fs::directory_iterator(path))
	{
		auto texture = ActiveTextureTrait::Create();
		if (!texture->LoadFromFile(entry.path().string()))
		{
			std::cerr << "Failed to load texture: " << entry.path() << "\n";
			continue;
		}
		m_resources.emplace(entry.path().filename().replace_extension().string(), std::move(texture));
	}
}
#endif

template<typename T>
T* ResourceLoader<T>::GetResource(const std::string& name)
{
	auto it = m_resources.find(name);
	return (it != m_resources.end()) ? it->second.get() : nullptr;
}

template<typename T>
bool ResourceLoader<T>::IsValidDirectory(const fs::path& path) const
{
	return fs::exists(path) && fs::is_directory(path);
}

template<typename T>
std::string ResourceLoader<T>::GetCleanName(const fs::path& path) const
{
	return path.filename().replace_extension().string();
}
