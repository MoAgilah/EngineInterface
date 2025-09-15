#pragma once

#include "../Interface/Resources/ITexture.h"
#include "../../Utilities/ResourceLoader.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager() = default;

	ITexture* GetTexture(const std::string& name);

	void AddTextures(const fs::path& path);

private:

	ResourceLoader<ITexture> m_loader;
};