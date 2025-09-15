#include "ShaderManager.h"

#include "../Core/Constants.h"

ShaderManager::ShaderManager()
	: m_loader(GameConstants::ShaderFilePaths)
{}

IShader* ShaderManager::GetShader(const std::string& name)
{
	return m_loader.GetResource(name);
}

void ShaderManager::AddShaders(const fs::path& path)
{
	m_loader.LoadResources(path);
}