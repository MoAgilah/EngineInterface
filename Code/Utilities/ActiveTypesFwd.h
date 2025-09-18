#pragma once
#include "Defines.h"
#include <memory>

#include "../Engine/Interface/Resources/IFont.h"
#include "../Engine/Interface/Resources/IShader.h"
#include "../Engine/Interface/Resources/ITexture.h"
#include "../Engine/Interface/Resources/IMusic.h"
#include "../Engine/Interface/Resources/ISound.h"

#if USE_SFML

// Forward-declare the backend wrappers (no heavy includes here)
class SFFont;
class SFShader;
class SFTexture;
class SFMusic;
class SFSound;

// Active backend type aliases
using ActiveFont = SFFont;
using ActiveShader = SFShader;
using ActiveTexture = SFTexture;
using ActiveMusic = SFMusic;
using ActiveSound = SFSound;

// Factory function declarations (defined in backend)
std::unique_ptr<IFont>    MakeActiveFont();
std::unique_ptr<IShader>  MakeActiveShader();
std::unique_ptr<ITexture> MakeActiveTexture();
std::unique_ptr<IMusic>   MakeActiveMusic();
std::unique_ptr<ISound>   MakeActiveSound();

#else

using ActiveFont = IFont;
using ActiveShader = IShader;
using ActiveTexture = ITexture;
using ActiveMusic = IMusic;
using ActiveSound = ISound;

std::unique_ptr<IFont>    MakeActiveFont() { return nullptr; }
std::unique_ptr<IShader>  MakeActiveShader() { return nullptr; }
std::unique_ptr<ITexture> MakeActiveTexture() { return nullptr; }
std::unique_ptr<IMusic>   MakeActiveMusic() { return nullptr; }
std::unique_ptr<ISound>   MakeActiveSound() { return nullptr; }

#endif
