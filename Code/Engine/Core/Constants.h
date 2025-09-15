#pragma once

#include "../../Utilities/Traits.h"
#include "../../Utilities/Vector.h"
#include "../../Utilities/Colour.h"
#include <string>

#if USE_SFML

#include "../../Platform/SFML/Resource/SFFont.h"
#include "../../Platform/SFML/Resource/SFShader.h"
#include "../../Platform/SFML/Resource/SFTexture.h"
#include "../../Platform/SFML/Resource/SFMusic.h"
#include "../../Platform/SFML/Resource/SFSound.h"

using ActiveFontTrait = FontTrait<SFFont>;
using ActiveShaderTrait = ShaderTrait<SFShader>;
using ActiveTextureTrait = TextureTrait<SFTexture>;
using ActiveMusicTrait = MusicTrait<SFMusic>;
using ActiveSoundTrait = SoundTrait<SFSound>;

#endif


class GameConstants
{
public:
	static void Init();

	static bool DRender;
	static bool GameIsReady;
	static float FPS;
	static float Gravity;
	static float ObjectSpeed;
	static Colour WindowColour;
	static Vector2f ScreenDim;
	static Vector2f Scale;
	static std::string WindowTitle;
	static std::string TileFilePaths;
	static std::string FontFilePaths;
	static std::string ShaderFilePaths;
	static std::string SoundFilePaths;
	static std::string MusicFilePaths;
	static std::string TextureFilePaths;
};