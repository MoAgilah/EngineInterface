#include "Constants.h"

bool  GameConstants::DRender = false;
bool  GameConstants::GameIsReady = false;
float GameConstants::FPS = 60.f;
float GameConstants::ObjectSpeed = 2.f;
float GameConstants::Gravity = 9.81f;
Colour GameConstants::WindowColour = Colour(0, 0, 255);
Vector2f GameConstants::ScreenDim = Vector2f(600.f, 600.f);
Vector2f GameConstants::Scale = Vector2f(1.f, 1.f);
std::string GameConstants::WindowTitle = "SFML Game Engine";
std::string GameConstants::TileFilePaths = "../Resources/TileTypes.txt";
std::string GameConstants::FontFilePaths = "../SFMLEngine/EngineInterface/Resources/Fonts/";
std::string GameConstants::ShaderFilePaths = "../SFMLEngine/EngineInterface/Resources/Shaders/";
std::string GameConstants::SoundFilePaths = "../SFMLEngine/EngineInterface/Resources/Sounds/";
std::string GameConstants::MusicFilePaths = "../SFMLEngine/EngineInterface/Resources/Music/";
std::string GameConstants::TextureFilePaths = "../SFMLEngine/EngineInterface/Resources/Textures/";

void GameConstants::Init()
{
	// Touch the values so linker pulls this file in early
	(void)DRender;
	(void)GameIsReady;
	(void)FPS;
	(void)WindowColour;
	(void)ScreenDim;
	(void)Scale;
	(void)WindowTitle;
	(void)TileFilePaths;
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