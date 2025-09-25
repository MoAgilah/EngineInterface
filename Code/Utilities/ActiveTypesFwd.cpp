#include "ActiveTypesFwd.h"

#if USE_SFML

#else

std::unique_ptr<IFont>    MakeActiveFont() { return nullptr; }
std::unique_ptr<IMusic>   MakeActiveMusic() { return nullptr; }
std::unique_ptr<ISound>   MakeActiveSound() { return nullptr; }
std::unique_ptr<IShader>  MakeActiveShader() { return nullptr; }
std::unique_ptr<ITexture> MakeActiveTexture() { return nullptr; }

#endif