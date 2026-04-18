#pragma once

#include "ActiveTypesFwd.h"
#include "Traits.h"
#include "../Utilities/Logger.h"

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <format>

namespace fs = std::filesystem;

template<typename T>
class ResourceLoader
{
public:
	ResourceLoader() = default;
	explicit ResourceLoader(const std::string& path) { LoadResources(path); }
	virtual ~ResourceLoader() = default;

	T* GetResource(const std::string& name);
	void LoadResources(const fs::path& path);

private:
	bool IsValidDirectory(const fs::path& path) const;
	std::string GetCleanName(const fs::path& path) const;

	std::unordered_map<std::string, std::unique_ptr<T>> m_resources;
};

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

template<typename T>
void ResourceLoader<T>::LoadResources(const fs::path& path)
{
	if (!IsValidDirectory(path))
		return;

	for (const auto& entry : fs::directory_iterator(path))
	{
		if (!entry.is_regular_file())
			continue;

		auto resource = ResourceTraits<T>::Create();
		if (!resource)
			continue;

		if (!resource->LoadFromFile(entry.path().string()))
		{
			Logger::GetDefaultLogger().Log(
				LogLevel::Warning,
				std::format("Failed to load {} from {}",
					ResourceTraits<T>::TypeName,
					entry.path().string()));
			continue;
		}

		m_resources.emplace(GetCleanName(entry.path()), std::move(resource));
	}
}

template<typename T>
T* ResourceLoader<T>::GetResource(const std::string& name)
{
	auto it = m_resources.find(name);

	if (it != m_resources.end())
		return it->second.get();

	return nullptr;
}