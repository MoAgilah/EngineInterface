#pragma once

#include "../../../Utilities/Vector2.h"
#include "../../../Utilities/Rect.h"
#include <string_view>
#include <vector>

class IRenderer;

class ISprite
{
public:
	virtual ~ISprite() = default;

	virtual void Update(float dt) = 0;
	virtual void Render(IRenderer* renderer) = 0;

	std::string_view GetTexID() const { return m_texID; }

	virtual bool SetTexture(const std::string& texId) = 0;

	virtual void SetDirection(bool dir) = 0;

	virtual Vector2u GetTextureSize() const = 0;
	virtual void SetTextureRect(const IntRect& rect) = 0;

protected:

	std::string m_texID;
};

struct Range
{
	int m_current = 0;
	int m_max = 0;
};

class IAnimatedSprite
{
public:
	IAnimatedSprite(float animSpeed, float frameDurationMs)
		: m_animSpeed(animSpeed), m_frameDuration(frameDurationMs / 1000.0f)
	{}

	virtual ~IAnimatedSprite() = default;

	virtual void Update(float dt);

	Vector2u GetFrameSize() const { return m_frameSize; }
	virtual void SetFrameSize(const Vector2u& size) = 0;

	void ChangeAnim(int animNum);
	int GetCurrentAnim() const { return m_animation.m_current; }

	void EnsureAnim(int anim);

	void SetFrames(const std::vector<int>& numFrames);
	virtual void SetFrameData(int rows, int columns, const std::vector<int>& numFrames) = 0;

	bool PlayedNumTimes(int val) const { return m_animCycles == val; }
	bool PlayedOnce() const { return m_animCycles > 0; }

	void SetShouldLoop(bool loop) { m_loop = loop; }

	float GetCurrAnimSpeed() const { return m_animSpeed; }
	void UpdateAnimSpeed(float animSpd);

protected:

	Range m_frame;
	Range m_animation;
	bool m_loop = true;
	int m_animCycles = 0;
	float m_animSpeed = 0;
	float m_currentTime = 0;
	float m_frameDuration = 0;
	Vector2u m_frameSize;
	std::vector<int> m_numFrames;
};

