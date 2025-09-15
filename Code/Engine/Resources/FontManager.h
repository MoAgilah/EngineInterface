#pragma once

#include "../Interface/Resources/IFont.h"
#include "../../Utilities/ResourceLoader.h"

class FontManager
{
public:
	FontManager();
	~FontManager() = default;

	IFont* GetFont(const std::string& name);
	void AddFonts(const fs::path& path);

private:

	ResourceLoader<IFont> m_loader;
};