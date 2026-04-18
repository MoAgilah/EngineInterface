#pragma once

#include "ActiveTypesFwd.h"

template <typename T>
struct CapsuleTraits;

template<typename T>
struct ResourceTraits;

template<>
struct ResourceTraits<IFont>
{
    static std::unique_ptr<IFont> Create() { return MakeActiveFont(); }
    static constexpr const char* TypeName = "font";
};

template<>
struct ResourceTraits<ITexture>
{
    static std::unique_ptr<ITexture> Create() { return MakeActiveTexture(); }
    static constexpr const char* TypeName = "texture";
};

template<>
struct ResourceTraits<IShader>
{
    static std::unique_ptr<IShader> Create() { return MakeActiveShader(); }
    static constexpr const char* TypeName = "shader";
};

template<>
struct ResourceTraits<ISound>
{
    static std::unique_ptr<ISound> Create() { return MakeActiveSound(); }
    static constexpr const char* TypeName = "sound";
};

template<>
struct ResourceTraits<IMusic>
{
    static std::unique_ptr<IMusic> Create() { return MakeActiveMusic(); }
    static constexpr const char* TypeName = "music";
};