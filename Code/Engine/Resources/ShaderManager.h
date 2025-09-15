#pragma once

#include "../Interface/Resources/IShader.h"
#include "../../Utilities/ResourceLoader.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager() = default;

	IShader* GetShader(const std::string& name);
	void AddShaders(const fs::path& path);

private:

	ResourceLoader<IShader> m_loader;
};