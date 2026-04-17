#pragma once


#include "../../Utilities/Colour.h"
#include "../../Utilities/Vector2.h"
#include <string>
#include <filesystem>

class GameConstants
{
public:
	static void Init();
	static Vector2f ScaleScreenDim(float x, float y);
	static std::filesystem::path GetDefaultLogPath();

	static bool DRender;
	static bool GameIsReady;
	static float FPS;
	static float CountdownDuration;
	static float Gravity;
	static float ObjectSpeed;
	static Colour WindowColour;
	static Vector2f ScreenDim;
	static Vector2f ViewDim;
	static Vector2f Scale;
	static std::string WindowTitle;
	static std::string DefaultOutputPath;
	static std::string TileFilePaths;
	static std::string FontFilePaths;
	static std::string ShaderFilePaths;
	static std::string SoundFilePaths;
	static std::string MusicFilePaths;
	static std::string TextureFilePaths;
};