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

namespace ResourceUtils
{
	inline bool IsValidDirectory(const fs::path& path)
	{
		return fs::exists(path) && fs::is_directory(path);
	}

	inline std::string GetCleanName(const fs::path& path)
	{
		auto file = path.filename();
		file.replace_extension();
		return file.string();
	}
}

template<typename T>
class ResourceLoader
{
public:
	ResourceLoader() = default;
	explicit ResourceLoader(const fs::path& path) { LoadResources(path); }
	virtual ~ResourceLoader() = default;

	T* GetResource(const std::string& name);
	void LoadResources(const fs::path& path);

	size_t GetResourceCount() const { return m_resources.size(); }

private:

	std::unordered_map<std::string, std::unique_ptr<T>> m_resources;
};

template<typename T>
void ResourceLoader<T>::LoadResources(const fs::path& path)
{
	if (!ResourceUtils::IsValidDirectory(path))
	{
		::Logger::GetDefaultLogger().Log(
			LogLevel::Info,
			std::format("Skipping resource directory: {}", path.string()));
		return;
	}

	::Logger::GetDefaultLogger().Log(
		LogLevel::Info,
		std::format("Loading resources from {}", path.string()));

	for (const auto& entry : fs::directory_iterator(path))
	{
		if (!entry.is_regular_file())
			continue;

		auto resource = ResourceTraits<T>::Create();
		if (!resource)
		{
			::Logger::GetDefaultLogger().Log(
				LogLevel::Warning,
				std::format("Failed to create {} resource for {}",
					ResourceTraits<T>::TypeName,
					entry.path().string()));
			continue;
		}

		if (!resource->LoadFromFile(entry.path().string()))
		{
			::Logger::GetDefaultLogger().Log(
				LogLevel::Warning,
				std::format("Failed to load {} from {}",
					ResourceTraits<T>::TypeName,
					entry.path().string()));
			continue;
		}

		const auto name = ResourceUtils::GetCleanName(entry.path());

		auto [it, inserted] = m_resources.emplace(name, std::move(resource));

		if (!inserted)
		{
			::Logger::GetDefaultLogger().Log(
				LogLevel::Debug,
				std::format("Skipped duplicate {} '{}' from {}",
					ResourceTraits<T>::TypeName,
					name,
					entry.path().string()));
		}
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