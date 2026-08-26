#pragma once

#include "../Engine/Interface/Resources/IFont.h"
#include "../Engine/Interface/Resources/IMusic.h"
#include "../Engine/Interface/Resources/IShader.h"
#include "../Engine/Interface/Resources/ISound.h"
#include "../Engine/Interface/Resources/ITexture.h"
#include <memory>

std::unique_ptr<IFont>    MakeActiveFont();
std::unique_ptr<IMusic>   MakeActiveMusic();
std::unique_ptr<ISound>   MakeActiveSound();
std::unique_ptr<IShader>  MakeActiveShader();
std::unique_ptr<ITexture> MakeActiveTexture();