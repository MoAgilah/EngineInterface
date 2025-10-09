#pragma once


#include "../../Utilities/Colour.h"
#include "../../Utilities/Vector.h"
#include <string>

class GameConstants
{
public:
	static void Init();
	static Vector2f ScaleScreenDim(float x, float y);

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