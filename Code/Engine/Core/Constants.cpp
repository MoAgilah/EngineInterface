#include "Constants.h"

#include "..\..\Utilities\LogFormatter.h"
#include <format>

bool  GameConstants::DRender = false;
bool  GameConstants::GameIsReady = false;
float GameConstants::FPS = 60.f;
float GameConstants::CountdownDuration = 300.f;
float GameConstants::ObjectSpeed = 2.f;
float GameConstants::Gravity = 9.81f;
Colour GameConstants::WindowColour = Colour(0, 0, 255);
Vector2f GameConstants::ScreenDim = Vector2f(600.f, 600.f);
Vector2f GameConstants::ViewDim = GameConstants::ScreenDim;
Vector2f GameConstants::Scale = Vector2f(1.f, 1.f);
std::string GameConstants::WindowTitle = "Game Engine";
std::string GameConstants::FontFilePaths = "Resources/Fonts/";
std::string GameConstants::ShaderFilePaths = "Resources/Shaders/";
std::string GameConstants::SoundFilePaths = "Resources/Sounds/";
std::string GameConstants::MusicFilePaths = "Resources/Music/";
std::string GameConstants::TextureFilePaths = "Resources/Textures/";

void GameConstants::Init()
{
	// Touch the values so linker pulls this file in early
#if defined(_DEBUG) || defined(DEBUG)
	DRender = true;
#else
	DRender = false;
#endif
	(void)GameIsReady;
	(void)FPS;
	(void)CountdownDuration;
	(void)WindowColour;
	(void)ScreenDim;
	(void)Scale;
	(void)WindowTitle;
	(void)FontFilePaths;
	(void)ShaderFilePaths;
	(void)SoundFilePaths;
	(void)MusicFilePaths;
	(void)TextureFilePaths;
}

Vector2f GameConstants::ScaleScreenDim(float x, float y)
{
	return { ScreenDim.x * x,ScreenDim.y * y };
}
