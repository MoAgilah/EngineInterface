#include "ISprite.h"

#include "../../../Utilities/Guards.h"
#include <format>

void IAnimatedSprite::Update(float dt)
{
	ThrowIfFalse(
		m_frame.m_max > 0,
		"Animation frames must be configured before updating."
	);

	if (!m_loop && m_animCycles > 0)
		return;

	m_currentTime += m_animSpeed * dt;

	while (m_currentTime >= m_frameDuration)
	{
		m_currentTime -= m_frameDuration;

		++m_frame.m_current;

		if (m_frame.m_current >= m_frame.m_max)
		{
			++m_animCycles;

			if (m_loop)
			{
				m_frame.m_current = 0;
			}
			else
			{
				--m_frame.m_current;
				break;
			}
		}
	}
}

void IAnimatedSprite::ChangeAnim(int animNum)
{
	ThrowIfFalse(
		0 <= animNum && animNum < m_animation.m_max,
		std::format(
			"Animation index {} is out of range [0, {}).",
			animNum,
			m_animation.m_max
		)
	);

	m_animation.m_current = animNum;

	m_frame.m_current = 0;
	m_frame.m_max = m_numFrames[m_animation.m_current];

	m_currentTime = 0.0f;
	m_animCycles = 0;
}

void IAnimatedSprite::EnsureAnim(int anim)
{
	if (GetCurrentAnim() != anim)
		ChangeAnim(anim);
}

void IAnimatedSprite::SetFrames(const std::vector<int>& numFrames)
{
	ThrowIfFalse(
		!numFrames.empty(),
		"Animation frame data cannot be empty."
	);

	for (size_t i = 0; i < numFrames.size(); ++i)
	{
		ThrowIfFalse(
			numFrames[i] > 0,
			std::format(
				"Animation frame count at index {} must be greater than zero.",
				i
			)
		);
	}

	m_numFrames.assign(numFrames.begin(), numFrames.end());

	m_currentTime = 0.0f;

	m_animation.m_current = 0;
	m_animation.m_max = static_cast<int>(m_numFrames.size());

	m_frame.m_current = 0;
	m_frame.m_max = m_numFrames[m_animation.m_current];
}

void IAnimatedSprite::UpdateAnimSpeed(float animSpd)
{
	ThrowIfFalse(
		animSpd >= 0.0f,
		"Animation speed cannot be negative."
	);

	if (m_animSpeed != animSpd)
		m_animSpeed = animSpd;
}