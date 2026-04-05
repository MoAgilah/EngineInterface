#include "CountdownTimerWrapper.h"


namespace EngineInterface
{
    namespace Managed
    {
        namespace Engine
        {
            namespace Core
            {
                CountdownTimerWrapper::CountdownTimerWrapper(float maxTime)
                {
                    m_countdownTimer = new CountdownTimer(maxTime);
                }

                CountdownTimerWrapper::~CountdownTimerWrapper()
                {
                    this->!CountdownTimerWrapper();
                }

                CountdownTimerWrapper::!CountdownTimerWrapper()
                {
                    if (m_countdownTimer != nullptr)
                    {
                        delete m_countdownTimer;
                        m_countdownTimer = nullptr;
                    }
                }

                void CountdownTimerWrapper::Update(float deltaTime)
                {
                    m_countdownTimer->Update(deltaTime);
                }

                float CountdownTimerWrapper::GetCurrTime()
                {
                    return m_countdownTimer->GetCurrTime();
                }

                void CountdownTimerWrapper::SetCurrTime(float time)
                {
                    m_countdownTimer->SetCurrTime(time);
                }

                bool CountdownTimerWrapper::CheckEnd()
                {
                    return m_countdownTimer->CheckEnd();
                }

                void CountdownTimerWrapper::ForceEnd()
                {
                    m_countdownTimer->ForceEnd();
                }

                void CountdownTimerWrapper::Pause()
                {
                    m_countdownTimer->Pause();
                }
                void CountdownTimerWrapper::Resume()
                {
                    m_countdownTimer->Resume();
                }

                void CountdownTimerWrapper::RestartTimer()
                {
                    m_countdownTimer->RestartTimer();
                }

                void CountdownTimerWrapper::SetMaxTime(float maxTime)
                {
                    m_countdownTimer->SetMaxTime(maxTime);
                }

                float CountdownTimerWrapper::GetMaxTime()
                {
                    return m_countdownTimer->GetMaxTime();
                }
            }
        }
    }
}