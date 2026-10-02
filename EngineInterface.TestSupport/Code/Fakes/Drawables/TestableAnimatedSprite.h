#pragma once

#include <Engine/Interface/Drawables/ISprite.h>

class TestableAnimatedSprite : public IAnimatedSprite
{
public:
	TestableAnimatedSprite(float animSpeed, float frameDurationMs)
		: IAnimatedSprite(animSpeed, frameDurationMs)
	{}

	void SetFrameSize(const Vector2u& size) override
	{
		m_frameSize = size;
	}

	void SetFrameData(int rows, int columns, const std::vector<int>& numFrames) override
	{
		SetFrames(numFrames);
	}

	int GetCurrentFrame() const
	{
		return m_frame.m_current;
	}
};

