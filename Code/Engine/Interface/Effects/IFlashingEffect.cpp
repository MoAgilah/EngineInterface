#include "IFlashingEffect.h"

#include "../../../Utilities/Guards.h"

IFlashingEffect::IFlashingEffect(IShader* shader, float flashDuration, bool loop)
    : IShaderEffect(shader), m_flashDuration(flashDuration), m_timer(m_flashDuration), m_looping(loop)
{
    ThrowIfFalse(
        flashDuration > 0.f,
        "Flash duration must be greater than zero"
    );
}

void IFlashingEffect::Update(float deltaTime)
{
    if (m_paused)
        return;

    m_timer.Update(deltaTime);

    if (m_timer.CheckEnd())
    {
        if (!m_looping)
        {
            m_paused = true;
        }
        else
        {
            m_reduceAlpha = !m_reduceAlpha;
            m_timer.RestartTimer();
        }
    }

    float progress =
        m_timer.GetCurrTime() / m_timer.GetMaxTime();

    float alpha = m_reduceAlpha
        ? progress
        : 1.f - progress;

    GetShader()->SetUniform("time", alpha);
}

void IFlashingEffect::SetIsPaused(bool paused)
{
    m_paused = paused;

    if (paused)
        m_timer.Pause();
    else
        m_timer.Resume();
}