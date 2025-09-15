#include "TextureManager.h"

#include "../Core/Constants.h"

TextureManager::TextureManager()
	: m_loader(GameConstants::TextureFilePaths)
{
}

ITexture* TextureManager::GetTexture(const std::string& name)
{
	return m_loader.GetResource(name);
}

void TextureManager::AddTextures(const fs::path& path)
{
	m_loader.LoadResources(path);
}
