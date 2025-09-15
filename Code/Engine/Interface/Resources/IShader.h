#pragma once

#include <string>
#include <optional>
#include <algorithm>

enum class ShaderType
{
    Vertex,
    Fragment,
    Geometry
};

class IShader
{
public:
    virtual ~IShader() = default;
    virtual bool LoadFromFile(const std::string& filepath) = 0;

protected:
    inline std::optional<ShaderType> ShaderTypeFromExtension(std::string ext)
    {
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        if (ext == "vert")
            return ShaderType::Vertex;
        if (ext == "frag")
            return ShaderType::Fragment;
        if (ext == "geom")
            return ShaderType::Geometry;

        return std::nullopt;
    }
};
