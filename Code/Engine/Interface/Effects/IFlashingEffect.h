#pragma once

#include "IShaderEffect.h"
#include "../Resources/IShader.h"
#include "../../Core/CountdownTimer.h"

class IFlashingEffect : public IShaderEffect
{
public:
	IFlashingEffect(IShader* shader, float flashDuration, bool loop = true);
	virtual ~IFlashingEffect() = default;

	void Update(float deltaTime) override;

	bool GetIsLooping() const { return m_looping; }
	void SetIsLooping(bool loop) { m_looping = loop; }

	bool GetIsPaused() const { return m_paused; }
	void SetIsPaused(bool paused);

protected:

	bool m_paused = false;
	bool m_looping = true;
	bool m_reduceAlpha = true;
	float m_flashDuration = 0.f;
	CountdownTimer m_timer;
};