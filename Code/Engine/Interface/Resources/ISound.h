#pragma once

#include <string>

class ISound
{
public:
    virtual ~ISound() = default;

    // Load a music stream from a file
    virtual bool LoadFromFile(const std::string& filepath) = 0;

    // Playback control
    virtual void Play() = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;

    // Looping
    virtual void SetLoop(bool loop) = 0;
};