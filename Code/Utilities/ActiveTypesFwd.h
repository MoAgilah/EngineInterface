#pragma once

#include "Defines.h"
#include "../Engine/Interface/Resources/IFont.h"
#include "../Engine/Interface/Resources/IMusic.h"
#include "../Engine/Interface/Resources/IShader.h"
#include "../Engine/Interface/Resources/ISound.h"
#include "../Engine/Interface/Resources/ITexture.h"
#include <memory>

#if USE_SFML

// Forward-declare the backend wrappers (no heavy includes here)
class SFFont;
class SFMusic;
class SFShader;
class SFSound;
class SFTexture;

// Active backend type aliases
using ActiveFont = SFFont;
using ActiveMusic = SFMusic;
using ActiveShader = SFShader;
using ActiveSound = SFSound;
using ActiveTexture = SFTexture;

// Factory function declarations (defined in backend)
std::unique_ptr<IFont>    MakeActiveFont();
std::unique_ptr<IMusic>   MakeActiveMusic();
std::unique_ptr<IShader>  MakeActiveShader();
std::unique_ptr<ISound>   MakeActiveSound();
std::unique_ptr<ITexture> MakeActiveTexture();

#else

using ActiveFont = IFont;
using ActiveMusic = IMusic;
using ActiveShader = IShader;
using ActiveSound = ISound;
using ActiveTexture = ITexture;

std::unique_ptr<IFont>    MakeActiveFont();
std::unique_ptr<IMusic>   MakeActiveMusic();
std::unique_ptr<ISound>   MakeActiveSound();
std::unique_ptr<IShader>  MakeActiveShader();
std::unique_ptr<ITexture> MakeActiveTexture();

#endif
